#!/bin/bash

#vulnerable version
docker run --name lighttpd forallsecure/lighttpd:vulnerable
#fixed version
#docker run --name lighttpd forallsecure/lighttpd:fixed
