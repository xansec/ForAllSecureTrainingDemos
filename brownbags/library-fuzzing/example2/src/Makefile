.PHONY: all clean
all: example2

clean:
	rm -rf example2 ex2lib.so

example2: ex2.cxx ex2lib.so ex2lib.hxx
	g++ -std=c++03 -O0 -o $@ ex2.cxx -I. ./ex2lib.so
	strip $@

%.so: %.c
	gcc -std=c99 -shared -fPIC -O0 -o $@ $^
	strip $@

%.so: %.cxx
	g++ -std=c++03 -shared -fPIC -O0 -o $@ $^
	strip $@
