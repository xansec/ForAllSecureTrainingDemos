FROM rust AS builder 
RUN apt-get update && apt-get install -y binutils-dev libunwind-dev libglib2.0-dev libpixman-1-dev
#RUN export RUSTFLAGS="-Znew-llvm-pass-manager=no -Awarnings"
RUN mkdir /fuzz
WORKDIR /fuzz
COPY . .
#RUN mv ./testsuite /testsuite
RUN cargo install --force honggfuzz --no-default-features
WORKDIR /fuzz/bitcoin_hfuzz_deserialize
RUN cargo hfuzz build
WORKDIR /fuzz/bitcoin_hfuzz_serialize
RUN cargo hfuzz build

FROM ubuntu
COPY --from=builder /fuzz/bitcoin_hfuzz_serialize/hfuzz_target/x86_64-unknown-linux-gnu/release/bitcoin_hfuzz_serialize /
COPY --from=builder /fuzz/bitcoin_hfuzz_deserialize/hfuzz_target/x86_64-unknown-linux-gnu/release/bitcoin_hfuzz_deserialize /
