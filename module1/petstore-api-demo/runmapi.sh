#!/bin/bash

mapi run \
     petstore-demo 120 'http://localhost/openapi.json' \
     --header-auth 'api_key: special-key' \
     --header-auth 'Authorization: Bearer 123' \
     --sarif 'output.sarif' \
     --url 'http://localhost/v3/' \
     --interactive

