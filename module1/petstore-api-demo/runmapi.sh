#!/bin/bash

set -ex

mapi run \
     forallsecure/petstore-demo 30 'http://localhost/openapi.json' \
     --header-auth 'api_key: special-key' \
     --sarif 'output.sarif' \
     --url 'http://localhost/v3/' \
     --interactive \
     "${@}" 

