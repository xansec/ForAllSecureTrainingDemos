FROM ubuntu 
RUN apt-get update && \
    apt-get install -y gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu binutils-aarch64-linux-gnu-dbg make build-essential
COPY . .
RUN make
