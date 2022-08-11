#!/bin/bash

#vulnerable version
docker run --rm --name lighttpd training.forallsecure.com:5000/forallsecure/tutorial/lighttpd:1.4.15
#fixed version
#docker run --rm --name lighttpd training.forallsecure.com:5000/forallsecure/tutorial/lighttpd:1.4.52
