CXX=clang++
FUZZ=./fuzz_binary_archive_symmetry

target:
	$(CXX) -g -O1 -fsanitize=fuzzer,address fuzz_binary_archive_symmetry.cpp -o fuzz_binary_archive_symmetry
fuzz:
	$(FUZZ) corpus -max_len=100
build-gcov:
	$(CXX) --coverage fuzz_binary_archive_symmetry.cpp -c 
	$(CXX) --coverage fuzz_binary_archive_symmetry.o -o fuzz_binary_archive_symmetry
run-gcov: 
	gcov -abcfu fuzz_binary_archive_symmetry.cpp -m
run-lcov:
	lcov --directory . --zerocounters
	lcov --directory . --capture --output-file cereal_bin_ar.info
	genhtml -o lcov-output/ cereal_bin_ar.info
clean:
	-rm -rf fuzz_binary_archive_symmetry *.o *.out *.fuzz *.TXT *.html *.info *.css *.gcov *.gz *.gcda *.gcno home/ bits/ ext/ usr/ lcov-output/
