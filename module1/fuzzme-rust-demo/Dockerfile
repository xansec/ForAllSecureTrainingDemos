FROM fuzzers/cargo-fuzz:0.10.0
RUN apt-get update && apt-get install -y binutils-dev libunwind-dev libglib2.0-dev libpixman-1-dev
RUN export FUZZ_CXXFLAGS="-O2 -fno-omit-frame-pointer -g -fsanitize=address \
    -fsanitize-coverage=edge,trace-pc-guard,indirect-calls,trace-cmp,trace-div,trace-gep"
RUN mkdir /fuzz-source
WORKDIR /fuzz-source
COPY . .
RUN mv ./testsuite /testsuite
RUN cargo install honggfuzz
RUN make base
RUN cp ./fuzzme-base /
RUN make clean libfuzzer
RUN cp ./fuzz/target/x86_64-unknown-linux-gnu/release/fuzzme-libfuzzer /
RUN make clean honggfuzz
RUN cp ./hfuzz_target/x86_64-unknown-linux-gnu/release/fuzz-source /fuzzme-honggfuzz

# Set to fuzz!
#ENTRYPOINT []
#CMD [""]
