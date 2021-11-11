FROM debian:buster-slim 
RUN apt-get update && \
    apt-get install -y qemu-user qemu-user-static gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu binutils-aarch64-linux-gnu-dbg make build-essential
COPY . .
RUN make

# Set to fuzz!
ENTRYPOINT []
CMD qemu-aarch64 /fuzzme @@
