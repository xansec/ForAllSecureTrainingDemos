#!/bin/bash

mapi run \
     petstore-demo 120 'http://localhost/openapi.json' \
     --header-auth 'api_key: special-key' \
     --header-auth 'Authorization: Bearer ab421254-1411-42ec-b587-85ad69c1b190' \
     --sarif 'output.sarif' \
     --url 'http://localhost/v3/' \
     --interactive

