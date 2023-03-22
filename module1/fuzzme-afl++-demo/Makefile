CXX=afl-g++-fast
FUZZ=afl-fuzz

all:
	$(CXX) -o FuzzMe FuzzMe.cpp 
fuzz:
	$(FUZZ) -o out -i testsuite/ -- ./FuzzMe 
clean:
	-rm -rf FuzzMe *.o *.out *.fuzz 
