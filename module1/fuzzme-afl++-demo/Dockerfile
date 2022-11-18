FROM fuzzers/aflplusplus:3.12c
WORKDIR /
COPY . .
RUN make 

# Set to fuzz!
ENTRYPOINT ["afl-fuzz", "-i", "/testsuite", "-o", "/out"]
CMD ["/FuzzMe", "@@"]
