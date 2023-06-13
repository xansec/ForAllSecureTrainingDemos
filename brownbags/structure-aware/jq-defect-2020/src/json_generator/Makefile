CC=clang
CFLAGS=-g -fsanitize=fuzzer -I /usr/local/include/libprotobuf-mutator -lprotobuf -pthread -lprotobuf-mutator
CXX=clang++
CXXFLAGS=-g -fsanitize=fuzzer -I /usr/local/include/libprotobuf-mutator -lprotobuf -pthread -lprotobuf-mutator
PROTOC=protoc
PROTOCFLAGS=--cpp_out=.
PROTOBUF_SRCS=/src/libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.cc /src/libprotobuf-mutator/src/libfuzzer/libfuzzer_mutator.cc

all: fuzz_json_generator
clean:
	-rm -rf *.pb.cc *.pb.h *.o json_generator
json_proto:
	${PROTOC} ${PROTOCFLAGS} json.proto
fuzz_json_generator: json_proto
	${CXX} json_generator.cpp json_writer.cpp json.pb.cc ${PROTOBUF_SRCS} ${CXXFLAGS} -o fuzz_json_generator
