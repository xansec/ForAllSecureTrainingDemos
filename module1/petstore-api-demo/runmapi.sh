#!/bin/bash

mapi run \
     petstore-demo 20 'http://localhost/openapi.json' \
     --header-auth 'Authorization: Bearer dda2d467-8e9c-4993-9611-3c7acbe711f1' \
     --url 'http://localhost/v3/' \
     --interactive

