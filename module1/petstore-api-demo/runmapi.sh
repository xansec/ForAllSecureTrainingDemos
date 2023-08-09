#!/bin/bash

set -ex

mapi run \
     training/petstore/petstore 30 'http://localhost/openapi.json' \
     --header-auth 'api_key: special-key' \
     --sarif 'output.sarif' \
     --url 'http://localhost/v3/' \
     --interactive \
     "${@}" 

