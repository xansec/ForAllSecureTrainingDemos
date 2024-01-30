FROM debian:buster-slim as builder
RUN mkdir /fuzz
RUN apt-get update && apt-get install -y git-all
RUN git clone https://github.com/USCiLab/cereal.git /home/cereal
RUN mv /home/cereal/include/cereal /usr/local/include
COPY . /fuzz

FROM fuzzers/honggfuzz:1.9
#COPY --from=builder /usr/local/bin/honggfuzz /usr/local/bin/honggfuzz
#COPY --from=builder /usr/lib/x86_64-linux-gnu/libunwind-ptrace.so.0 /usr/lib/x86_64-linux-gnu/libunwind-ptrace.so.0
#COPY --from=builder /usr/lib/x86_64-linux-gnu/libunwind-x86_64.so.8 /usr/lib/x86_64-linux-gnu/libunwind-x86_64.so.8
#COPY --from=builder /usr/lib/x86_64-linux-gnu/libbfd-2.31.1-system.so /usr/lib/x86_64-linux-gnu/libbfd-2.31.1-system.so
#COPY --from=builder /usr/lib/x86_64-linux-gnu/libopcodes-2.31.1-system.so /usr/lib/x86_64-linux-gnu/libopcodes-2.31.1-system.so
#COPY --from=builder /usr/lib/x86_64-linux-gnu/libunwind.so.8 /usr/lib/x86_64-linux-gnu/libunwind.so.8
#COPY --from=builder /usr/lib/x86_64-linux-gnu/libasan.so.5 /usr/lib/x86_64-linux-gnu/libasan.so.5
COPY --from=builder /fuzz /fuzz
COPY --from=builder /usr/local/include /usr/local/include
WORKDIR /fuzz
RUN make sanitizer
RUN cp -r /fuzz/testsuite /testsuite

# Set to fuzz!
ENTRYPOINT ["honggfuzz", "-f", "/testsuite", "--"]
CMD ["/fuzz/fuzz_binary_archive_symmetry"]
