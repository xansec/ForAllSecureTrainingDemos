CXX=hfuzz-g++
CXXFLAGS=-ftest-coverage -fprofile-arcs 
HFFLAGS=-fsanitize=address
FUZZ=honggfuzz

sanitizer:
	$(CXX) $(HFFLAGS) -o FuzzMe FuzzMe.cpp 
no-sanitizer:
	$(CXX) FuzzMe.cpp -o FuzzMe
fuzz:
	$(FUZZ) --persistent -i corpus -- FuzzMe
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
	-rm -rf FuzzMe *.o *.out *.fuzz *.TXT *.html *.info *.css *.gcov *.gz *.gcda *.gcno HF.sanitizer.log.* lcov-output/ covout/ corpus/*.honggfuzz.cov
