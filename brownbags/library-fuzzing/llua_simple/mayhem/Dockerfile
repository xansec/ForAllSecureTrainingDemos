FROM ubuntu AS builder

RUN apt-get -y update && DEBIAN_FRONTEND=noninteractive apt-get -y install build-essential

COPY . .
RUN gcc solution/solution.c libllua.so -o llua_harness

FROM ubuntu
COPY --from=builder /llua_harness /libllua.so /
COPY --from=builder /testsuite /testsuite
ENV LD_LIBRARY_PATH=/
