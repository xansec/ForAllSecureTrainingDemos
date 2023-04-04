CXX=clang++
FUZZ=./fuzz_binary_archive_symmetry
TESTS=./testsuite

target:
	$(CXX) -g -O1 -fsanitize=fuzzer,address fuzz_binary_archive_symmetry.cc -o fuzz_binary_archive_symmetry
fuzz: target
	$(FUZZ) $(TESTS) -max_len=100
build-cov:
	$(CXX) -fsanitize=fuzzer,address -fprofile-instr-generate -fcoverage-mapping -o fuzz_binary_archive_symmetry fuzz_binary_archive_symmetry.cc
run-cov: build-cov
	LLVM_PROFILE_FILE="fuzz_binary_archive_symmetry.profraw" ./fuzz_binary_archive_symmetry $(TESTS) -max_len=100 -max_total_time=15
gen-cov: run-cov
	llvm-profdata merge fuzz_binary_archive_symmetry.profraw -o fuzz_binary_archive_symmetry.profdata
show-cov-file: gen-cov
	llvm-cov report ./fuzz_binary_archive_symmetry --instr-profile=fuzz_binary_archive_symmetry.profdata
show-cov-line: gen-cov
	llvm-cov show ./fuzz_binary_archive_symmetry --instr-profile=fuzz_binary_archive_symmetry.profdata
clean:
	-rm -rf fuzz_binary_archive_symmetry *.o *.out *.fuzz *.profdata *.profraw $(TESTS)
