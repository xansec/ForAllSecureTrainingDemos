#!/bin/bash

#vulnerable version
docker run -p 8080:80 --name lighttpd forallsecure/lighttpd:vulnerable
#fixed version
#docker run -p 8080:80 --name lighttpd forallsecure/lighttpd:fixed
