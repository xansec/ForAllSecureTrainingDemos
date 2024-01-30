FROM fuzzers/honggfuzz:1.9
COPY . .
RUN make sanitizer

FROM debian:buster-slim
COPY --from=0 /FuzzMe .
COPY --from=0 /testsuite /testsuite
COPY --from=0 /usr/local/bin/honggfuzz /usr/local/bin/honggfuzz
COPY --from=0 /usr/lib/x86_64-linux-gnu/libunwind-ptrace.so.0 /usr/lib/x86_64-linux-gnu/libunwind-ptrace.so.0
COPY --from=0 /usr/lib/x86_64-linux-gnu/libunwind-x86_64.so.8 /usr/lib/x86_64-linux-gnu/libunwind-x86_64.so.8
COPY --from=0 /usr/lib/x86_64-linux-gnu/libbfd-2.31.1-system.so /usr/lib/x86_64-linux-gnu/libbfd-2.31.1-system.so
COPY --from=0 /usr/lib/x86_64-linux-gnu/libopcodes-2.31.1-system.so /usr/lib/x86_64-linux-gnu/libopcodes-2.31.1-system.so
COPY --from=0 /usr/lib/x86_64-linux-gnu/libunwind.so.8 /usr/lib/x86_64-linux-gnu/libunwind.so.8
COPY --from=0 /usr/lib/x86_64-linux-gnu/libasan.so.5 /usr/lib/x86_64-linux-gnu/libasan.so.5

# Set to fuzz!
ENTRYPOINT ["honggfuzz", "-f", "/testsuite", "--"]
CMD ["/FuzzMe"]
