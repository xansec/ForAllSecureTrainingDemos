CXX=g++
AFLCXX=afl-g++
RUN=afl-fuzz
TESTS=./testsuite
FILE=test_portable_binary_archive_symmetry.cc
BIN=./test_portable_binary_archive_symmetry
NAME=test_portable_binary_archive_symmetry
INPUT=./input
OUTPUT=./output
ASAN=-fsanitize=address

target:
	$(CXX) -g -O1 $(FILE) -o $(BIN)
afl:
	$(AFLCXX) $(ASAN) -g -O1 $(FILE) -o $(BIN)
run: afl
	-mkdir $(INPUT)
	echo seed > $(INPUT)/seed
	$(RUN) -i $(INPUT) -o $(OUTPUT) -- $(BIN)
build-cov:
	$(CXX) $(ASAN) -fprofile-instr-generate -fcoverage-mapping -o $(BIN) $(FILE)
run-cov: build-cov
	LLVM_PROFILE_FILE="$(NAME).profraw" $(BIN) $(TESTS) -max_len=100 -max_total_time=15
gen-cov: run-cov
	llvm-profdata merge $(NAME).profraw -o $(NAME).profdata
show-cov-file: gen-cov
	llvm-cov report $(BIN) --instr-profile=$(NAME).profdata
show-cov-line: gen-cov
	llvm-cov show $(BIN) --instr-profile=$(NAME).profdata
clean:
	-rm -rf $(BIN) *.o *.out *.fuzz *.profdata *.profraw *.json *.drcov *.lcov core.* ./cov $(INPUT) $(OUTPUT) $(TESTS)
