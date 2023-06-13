CC=clang
CFLAGS=-g -c -I /usr/local/include/libprotobuf-mutator
CXX=clang++
CXXFLAGS=-g -c -I /usr/local/include/libprotobuf-mutator
FUZZER_FLAGS=-fsanitize=fuzzer -lonig -lprotobuf -lprotobuf-mutator
PROTOC=protoc
PROTOCFLAGS=--cpp_out=.

all: fuzz_json_parse
clean:
	-rm -rf *.pb.cc *.pb.h *.o fuzz_json_parse
json_proto:
	${PROTOC} ${PROTOCFLAGS} json.proto
	${CXX} ${CXXFLAGS} json.pb.cc
json_writer: json_proto
	${CXX} ${CXXFLAGS} json_writer.cpp
jq_parse:
	${CXX} ${CXXFLAGS} jq_parse.cpp
libfuzzer_macro:
	${CXX} ${CXXFLAGS} /src/libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.cc
libfuzzer_mutator:
	${CXX} ${CXXFLAGS} /src/libprotobuf-mutator/src/libfuzzer/libfuzzer_mutator.cc
fuzz_json_parse: json_writer jq_parse libfuzzer_macro libfuzzer_mutator
	${CXX} jq_parse.o json.pb.o json_writer.o libfuzzer_macro.o libfuzzer_mutator.o /usr/local/lib/libjq.a ${FUZZER_FLAGS} -o fuzz_json_parse
