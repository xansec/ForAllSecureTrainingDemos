# This demo is for the fuzzing fundamentals Mayhem training.

To run the vulnerable ligghttpd server, do
`docker run --rm -d forallsecure/lighttpd:vulnerable`

To determine your ip address, run
`docker container inspect <container name> | grep IPAddress`

To run the simple test cases, do
`nc <ipaddress> 80 < simplea (or simpleb, etc...)`

To run the fixed server, do
`docker run --rm -d forallsecure/lighttpd:fixed`

This version should not fail on the failing test case.
