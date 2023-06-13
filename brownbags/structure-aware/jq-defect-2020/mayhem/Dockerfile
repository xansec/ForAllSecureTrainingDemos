FROM ubuntu AS builder

RUN apt update && DEBIAN_FRONTEND=noninteractive apt install -y \
    protobuf-compiler libprotobuf-dev binutils pip git make clang \
    ninja-build liblzma-dev libz-dev pkg-config autoconf libtool yacc

RUN pip install cmake --upgrade

# Build libprotobuf-mutator
WORKDIR /src
RUN git clone https://github.com/google/libprotobuf-mutator
WORKDIR /src/libprotobuf-mutator
RUN mkdir build
WORKDIR build
RUN cmake .. -GNinja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug
# Dumb hack, see https://github.com/google/libprotobuf-mutator/issues/222
RUN sed -i 's/descriptor_->requires_utf8_validation()/true/' /src/libprotobuf-mutator/src/field_instance.h
RUN ninja
RUN ninja install

# checkout and build the desired version of jq
WORKDIR /src
ARG VERSION="5b9e63e4af339bc5867603f14441b4b4cbb9e175"
RUN git clone --no-checkout https://github.com/stedolan/jq
WORKDIR /src/jq
RUN git checkout -q $VERSION
RUN git submodule update --init && \
    autoreconf -fi && \
    ./configure CC=clang CFLAGS="-fsanitize=fuzzer-no-link -fsanitize=address" \
       --host=x86_64-linux-gnu --with-oniguruma=builtin --disable-docs && \
    make -j8 && \
    make install && \
    ldconfig

# Build harnesses
COPY ./src/ /src/harness
WORKDIR /src/harness/json_generator
RUN make all
WORKDIR /src/harness/json_parse
RUN make all
WORKDIR /src/harness/jq_pair
RUN make all
COPY ./mayhem/jq_fuzzer/testsuite /src/harness/testsuite/

FROM ubuntu

RUN apt update -y && DEBIAN_FRONTEND=noninteractive && apt install -y \
    libonig-dev libprotobuf-dev
RUN ln -s /lib/x86_64-linux-gnu/libonig.so /lib/x86_64-linux-gnu/libonig.so.4
COPY --from=builder /src/harness/json_generator/fuzz_json_generator /fuzz_json_generator
COPY --from=builder /src/harness/json_parse/fuzz_json_parse /fuzz_json_parse
COPY --from=builder /src/harness/jq_pair/fuzz_jq_pair /fuzz_jq_pair
COPY --from=builder /src/harness/testsuite /testsuite
# Convenience helper to run the fuzzer
CMD "/fuzz_jq_pair -detect_leaks=0 -close_fd_mask=3 -print_funcs=0 -print_pcs=0 /testsuite"
