FROM fuzzers/aflplusplus:3.12c
COPY . .
RUN make 

# Set to fuzz!
ENTRYPOINT ["afl-fuzz", "-i", "/corpus", "-o", "/out"]
CMD ["/FuzzMe", "@@"]
