# This demo is for the Mayhem fundamentals training.

To run the vulnerable ligghttpd server, do
`docker run --rm -d forallsecure/lighttpd:vulnerable`

To determine your ip address, run
`docker container inspect <container name> | grep IPAddress`

To run the simple test cases (or reproduce a crash!), do
`nc <ipaddress> 80 < testcase (simplea, crash, etc...)`

To run the fixed server, do
`docker run --rm -d forallsecure/lighttpd:fixed`

To run Mayhem, do
`mayhem run . -f Mayhemfile.vuln (or Mayhemfile.fixed)`

This version should not fail on the failing test case.
