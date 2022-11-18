FROM debian:buster-slim as builder
RUN apt-get update && \
    apt-get install -y gcc make libc6-dbg && \
    rm -rf /var/lib/apt/lists/*
RUN mkdir /testsuite
ADD ./testsuite /testsuite
COPY fuzzme.c .
RUN gcc -o fuzzme -Wno-div-by-zero -fno-stack-protector -zexecstack -no-pie fuzzme.c


# Set to fuzz!
ENTRYPOINT []
CMD /fuzzme @@
