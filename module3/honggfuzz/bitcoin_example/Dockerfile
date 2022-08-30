FROM fuzzers/cargo-fuzz:0.10.0
RUN apt-get update && apt-get install -y binutils-dev libunwind-dev libglib2.0-dev libpixman-1-dev
RUN export RUSTFLAGS="-Znew-llvm-pass-manager=no"
RUN mkdir /fuzz
WORKDIR /fuzz
COPY . .
#RUN mv ./corpus /corpus
RUN cargo install honggfuzz
WORKDIR /fuzz/bitcoin_hfuzz_deserialize
RUN cargo hfuzz build
RUN mv /fuzz/bitcoin_hfuzz_deserialize/hfuzz_target/x86_64-unknown-linux-gnu/release/bitcoin_hfuzz_deserialize /
WORKDIR /fuzz/bitcoin_hfuzz_serialize
RUN cargo hfuzz build
RUN mv /fuzz/bitcoin_hfuzz_serialize/hfuzz_target/x86_64-unknown-linux-gnu/release/bitcoin_hfuzz_serialize /

# Set to fuzz!
#ENTRYPOINT []
#CMD [""]
