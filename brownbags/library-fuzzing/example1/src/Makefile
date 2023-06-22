.PHONY: all clean
all: example1

clean:
	rm -rf example1 MyCustomCxxLib.so my_custom_c_lib.so

example1: main.cpp MyCustomCxxLib.so MyCustomCxxLib.h my_custom_c_lib.so my_custom_c_lib.h
	g++ -std=c++03 -O0 -o $@ main.cpp MyCustomCxxLib.so my_custom_c_lib.so
	strip $@

%.so: %.c
	gcc -std=c99 -shared -fPIC -O0 -o $@ $^
	strip $@

%.so: %.cxx
	g++ -std=c++03 -shared -fPIC -O0 -o $@ $^
	strip $@
