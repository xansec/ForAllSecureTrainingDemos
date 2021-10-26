#!/bin/bash

#docker pull openapitools/openapi-petstore
docker run -it -e OPENAPI_BASE_PATH=/v3 -p 80:8080 openapitools/openapi-petstore
