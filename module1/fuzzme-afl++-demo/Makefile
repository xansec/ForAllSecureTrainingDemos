CXX=afl-g++-fast
FUZZ=afl-fuzz

all:
	$(CXX) -o FuzzMe FuzzMe.cpp 
fuzz:
	$(FUZZ) -o out -i corpus/ -- ./FuzzMe @@
clean:
	-rm -rf FuzzMe *.o *.out *.fuzz 
