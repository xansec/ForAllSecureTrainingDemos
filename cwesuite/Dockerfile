FROM ubuntu as builder

RUN apt update -y && apt install -y libc6-dbg gcc make

RUN mkdir /workspace
COPY . /workspace
WORKDIR /workspace

RUN make clean advanced basic all

FROM ubuntu
RUN mkdir /workspace
COPY --from=builder /workspace /workspace
RUN mv /workspace/testsuite /testsuite
