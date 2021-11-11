CXX=clang++
CXXFLAGS=-ftest-coverage -fprofile-arcs 
LLVMFLAGS=address
FUZZ=./FuzzMe

sanitizer:
	$(CXX) -fsanitize=fuzzer,$(LLVMFLAGS) -o FuzzMe FuzzMe.cpp 
no-sanitizer:
	$(CXX) -fsanitize=fuzzer FuzzMe.cpp -o FuzzMe
fuzz:
	$(FUZZ) corpus -max_len=1000
build-gcov:
	$(CXX) $(HFFLAGS) $(CXXFLAGS) -o FuzzMe FuzzMe.cpp
	mv FuzzMe-FuzzMe.gcno FuzzMe.gcno
capture:
	$(foreach f,$(shell ls ./corpus),./FuzzMe ./corpus/$(f);)
run-gcov: 
	mv FuzzMe-FuzzMe.gcda FuzzMe.gcda
	gcov FuzzMe.cpp -m
run-lcov:
	lcov --capture --directory . --output-file FuzzMe.info
	genhtml -o lcov-output/ FuzzMe.info
clean:
	-rm -rf FuzzMe *.o *.out *.fuzz *.TXT *.html *.info *.css *.gcov *.gz *.gcda *.gcno HF.sanitizer.log.* lcov-output/ covout/ 
