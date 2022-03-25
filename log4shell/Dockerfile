FROM ubuntu:20.04 as jazzer-builder
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y clang git openjdk-11-jdk lld python-is-python3 curl
RUN git clone https://github.com/CodeIntelligenceTesting/jazzer.git
WORKDIR /jazzer
RUN curl -LO https://github.com/bazelbuild/bazelisk/releases/download/v1.11.0/bazelisk-linux-amd64 && chmod +x bazelisk-linux-amd64
RUN ./bazelisk-linux-amd64 build //:jazzer_release

FROM gradle as log4shell-builder
ADD ./ /mayhem-log4shell
WORKDIR /mayhem-log4shell
RUN gradle shadowJar

FROM ubuntu:20.04
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y openjdk-11-jdk && \
    rm -rf /var/lib/apt/lists/*
COPY --from=log4shell-builder /mayhem-log4shell/build/libs/log4shell-all.jar /
COPY --from=jazzer-builder /jazzer/bazel-bin/jazzer_release.tar.gz /
RUN tar xvf /jazzer_release.tar.gz
COPY ./corpus /

CMD ["/jazzer", "--cp=/log4shell-all.jar", "--target_class=com.forallsecure.log4shell.Log4ShellFuzz2"]

