import argparse
import os
import sys
import requests
import csv
import datetime as dt
import json
import base64
from requests.auth import HTTPBasicAuth
import logging

def testAPI(url, headers):
    logging.debug('Entering ' + sys._getframe().f_code.co_name)
    logging.info('Testing API connection...')
    try:
        session.request('GET', url + '/api', headers=headers)
    except requests.exceptions.SSLError as e:
        logging.error('SSL error. Try running with --insecure or adding the invalid cert to your keystore.')
        logging.error(e)
        sys.exit(1)
    except BaseException as e:
        logging.error('Error validating API. Check your Mayhem url or token.')
        logging.error(e)
        sys.exit(1)
    return

def getIssue(api, headers, job_id, issue_id):
    logging.debug('Entering ' + sys._getframe().f_code.co_name)
    endpoint = api + '/issue/' + job_id + '/' + issue_id
    try:
        response = session.request('GET', endpoint, headers=headers)
        result = response.json()
    except BaseException as e:
        logging.error('Error getting issue - check your ID.')
        logging.error(e)
        sys.exit(1)
    return result

def getIssuesForJob(api, headers, job_id, offset=0):
    logging.debug('Entering ' + sys._getframe().f_code.co_name)
    endpoint = api + '/issue/' + job_id + '?limit=' + str(ELEMENTS)
    try:
        response = session.request('GET', endpoint, headers=headers)
        results = response.json()
        if len(results['items']) == ELEMENTS:
            results = results | getIssuesForJob(api, headers, job_id, (offset + ELEMENTS))
    except KeyError as e:
        logging.error('KeyError:' + str(e) + ', check your parameters.')
        sys.exit(1)
    return results['items']

def exportToJira(api, headers, issue_data):
    logging.debug('Entering ' + sys._getframe().f_code.co_name)
    endpoint = api['jira']['url'] + '/rest/api/2/issue/'
    auth = HTTPBasicAuth(api['jira']['username'], api['jira']['token'])
    #response = session.request('POST', api, headers=headers, json=issue_data)
    try:
        response = session.request('POST', endpoint, json=issue_data, auth=auth)
        resp_dict = json.loads(response.text)
        print('Issue ' + str(resp_dict['key']) + ' created.')
    except KeyError as e:
        logging.error('Issue not created, check your permssions and parameters.')
        logging.error(e)
        logging.error(resp_dict)
        sys.exit(1)
    return api['jira']['url'] + '/browse/' + str(resp_dict['key'])


OFFSET = 0
ELEMENTS = 100
# --todo-- Add additional fields as needed here

FORMAT = '''
{
    "fields": {
        "project":{
            "key": ""
        },
        "summary": "",
        "description": "",
        "issuetype": {
            "name": "Bug"
        }
    }
}
'''

if __name__ == '__main__':

    if(sys.version_info.major < 3):
        print('Please use Python 3.x or higher')
        sys.exit(1)

    parser = argparse.ArgumentParser()

    parser.add_argument('--job', required=True, type=str, help='The job ID to export (exports all issues found in a job)')
    parser.add_argument('--issue', type=str, help='The issue ID to export (exports a single issue from a job)')
    parser.add_argument('--config', type=str, default='jira.config', help='The JIRA configuration file (defaults to \'jira.config\')')
    parser.add_argument('--url', type=str, help='The mAPI URL')
    parser.add_argument('--token', type=str, help='The mAPI API access token')
    parser.add_argument('--log', type=str, default='warn', help='Log level (choose from debug, info, warning, error and critical)')
    parser.add_argument('--insecure', action='store_true', help='Disable SSL verification')
    parser.add_argument('--dry-run', action='store_true', help='Dry Run')


    args = parser.parse_args()

    levels = {
        'critical': logging.CRITICAL,
        'error': logging.ERROR,
        'warn': logging.WARNING,
        'warning': logging.WARNING,
        'info': logging.INFO,
        'debug': logging.DEBUG
    }

    session = requests.Session()
    if args.insecure:
        logging.warn('Setting urllib3 session to ignore insecure connections.')
        session.verify = False
        requests.packages.urllib3.disable_warnings(requests.packages.urllib3.exceptions.InsecureRequestWarning)
    loglevel = args.log.lower() if (args.log.lower() in levels) else 'warn'
    logging.basicConfig(stream=sys.stderr, level=levels[loglevel], format='%(asctime)s - %(levelname)s: %(message)s', datefmt='%Y-%m-%d %H:%M:%S')
    config = args.config
    if args.url:
        url = args.url
    elif os.environ.get('MAPI_URL'):
        url = os.environ.get('MAPI_URL')
    else:
        print('Please either set the url via the --url flag or $MAPI_URL variable')
        print(parser.print_help())
        sys.exit(1)
    if args.token:
        token = args.token
    elif os.environ.get('MAPI_TOKEN'):
        token = os.environ.get('MAPI_TOKEN')
    else:
        print('Please either set the API token via the --token flag or $MAPI_TOKEN variable')
        print(parser.print_help())
        sys.exit(1)

    mapi_api = url + '/api/v1'
    mapi_headers = {
        'accept': 'application/json',
        'Authorization': ('Bearer ' + token)
    }

    #Ensure API is correct
    testAPI(url, mapi_headers)

    with open(config, 'r') as config_file:
        config_data = config_file.read()
    jira_api = json.loads(config_data)
    #jira_api = jira['jira']['url'] + '/rest/api/2/issue/'
    jira_headers = {
        'Content-Type': 'application/json'
    }

    ticket = json.loads(FORMAT)
    ticket['fields']['project']['key'] = jira_api['jira']['project-key']

    job_id = str(args.job)
    if args.issue:
        issue_id = str(args.issue)
        issue = getIssue(mapi_api, mapi_headers, job_id, issue_id)
        ticket['fields']['summary'] = 'Mayhem issue ' + str(issue['id']) + ', job ' + str(issue['job_id']) + ': ' + str(issue['rule_id'])
        ticket['fields']['description'] = 'Endpoint: ' + str(issue['path']) + '\n' \
            + 'Method: ' + str(issue['method']) + '\n\n' \
            + 'Request: ' + base64.b64decode(issue['request']).decode('utf-8') + '\n\n' \
            + 'Response: ' + base64.b64decode(issue['response']).decode('utf-8') + '\n\n' \
            + 'Discovered on: ' + str(issue['created_at']) + '\n'
        # --todo-- Can set more fields here
        if not args.dry_run:
            link = exportToJira(jira_api, jira_headers, ticket)
            print('Link to newly created JIRA issue: ' + str(link))
        else:
            print(ticket)
    else:
        issues = getIssuesForJob(mapi_api, mapi_headers, job_id)
        for issue in issues:
            ticket['fields']['summary'] = 'Mayhem issue ' + str(issue['id']) + ', job ' + str(issue['job_id']) + ': ' + str(issue['rule_id'])
            ticket['fields']['description'] = 'Endpoint: ' + str(issue['path']) + '\n' \
                + 'Method: ' + str(issue['method']) + '\n\n' \
                + 'Request: ' + base64.b64decode(issue['request']).decode('utf-8') + '\n\n' \
                + 'Response: ' + base64.b64decode(issue['response']).decode('utf-8') + '\n\n' \
                + 'Discovered on: ' + str(issue['created_at']) + '\n'
                # --todo-- Can set more fields here
            if not args.dry_run:
                link = exportToJira(jira_api, jira_headers, ticket)
                print('Link to newly created JIRA issue: ' + str(link))
                sys.exit(0)
            else:
                print(ticket)
