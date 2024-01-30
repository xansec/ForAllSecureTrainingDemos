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
SCRIPT=./run_tests.sh

target:
	$(CXX) -g -O1 $(FILE) -o $(BIN)
afl:
	$(AFLCXX) $(ASAN) -g -O1 $(FILE) -o $(BIN)
run: afl
	-mkdir $(INPUT)
	echo seed > $(INPUT)/seed
	$(RUN) -i $(INPUT) -o $(OUTPUT) -- $(BIN)
build-cov:
	$(CXX) -g -fPIC -fprofile-arcs -ftest-coverage -Wall -Werror -o $(BIN) $(FILE)
run-cov: build-cov
	$(SCRIPT)
	gcov $(FILE)
gen-cov: run-cov
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory ./cov
clean:
	-rm -rf $(BIN) *.o *.out *.info *.json *.drcov *.lcov *.gcno *.gcda *.gcov core.* ./cov $(INPUT) $(OUTPUT)
