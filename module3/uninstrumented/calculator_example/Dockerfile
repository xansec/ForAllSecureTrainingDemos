FROM debian:bullseye
RUN apt-get update && apt-get install -y build-essential libc6-dbg
WORKDIR /build
COPY . .
RUN make
CMD ["/build/out/calculator"]
