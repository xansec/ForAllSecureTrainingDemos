FROM ubuntu as builder
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y git make g++
ADD . /mayhem
WORKDIR /mayhem

RUN git clone https://github.com/USCiLab/cereal.git
RUN cp -r ./cereal/include/cereal /usr/include
RUN make target

FROM ubuntu

COPY --from=builder /mayhem/test_portable_binary_archive_symmetry /

CMD ["/test_portable_binary_archive_symmetry"]
