FROM ubuntu:20.04 as builder
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y git make clang
ADD . /mayhem
WORKDIR /mayhem

RUN git clone https://github.com/USCiLab/cereal.git
RUN cp -r ./cereal/include/cereal /usr/include
RUN make 

FROM ubuntu:20.04

COPY --from=builder /mayhem/fuzz_binary_archive_symmetry /

CMD ["/fuzz_binary_archive_symmetry"]
