FROM debian:jessie-slim
RUN apt-get -y update && apt-get -y install build-essential
WORKDIR /root
COPY *.cxx *.hxx Makefile ./
RUN make
