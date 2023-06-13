CC=clang
CFLAGS=-g -c -I /usr/local/include/libprotobuf-mutator
CXX=clang++
CXXFLAGS=-g -c -I /usr/local/include/libprotobuf-mutator
FUZZER_FLAGS=-fsanitize=fuzzer,address -lonig -lprotobuf -lprotobuf-mutator
PROTOC=protoc
PROTOCFLAGS=--cpp_out=.

all: fuzz_jq_pair
clean:
	-rm -rf *.pb.cc *.pb.h *.o fuzz_jq_pair
json_proto:
	${PROTOC} ${PROTOCFLAGS} json.proto
	${CXX} ${CXXFLAGS} json.pb.cc
jq_proto:
	${PROTOC} ${PROTOCFLAGS} jq.proto
	${CXX} ${CXXFLAGS} jq.pb.cc
json_writer: json_proto
	${CXX} ${CXXFLAGS} json_writer.cpp
jq_writer: jq_proto
	${CXX} ${CXXFLAGS} jq_writer.cpp
jq_pair: json_writer jq_writer
	${CXX} ${CXXFLAGS} jq_pair.cpp
libfuzzer_macro:
	${CXX} ${CXXFLAGS} /src/libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.cc
libfuzzer_mutator:
	${CXX} ${CXXFLAGS} /src/libprotobuf-mutator/src/libfuzzer/libfuzzer_mutator.cc
fuzz_jq_pair: jq_pair libfuzzer_macro libfuzzer_mutator
	${CXX} jq_pair.o json.pb.o json_writer.o jq.pb.o jq_writer.o libfuzzer_macro.o libfuzzer_mutator.o /usr/local/lib/libjq.a ${FUZZER_FLAGS} -L /usr/local/lib -o fuzz_jq_pair
