## Lab 1: Basics

example1 is a toy program that makes use of custom shared libraries to echo its command line args back to stdout.

### Note

example1 is a C++ program, using one C++ library `MyCustomCxxLib.so` and one C library `my_custom_c_lib.so`. Feel free to look at the source before going through the exercise.

### Determining Shared Library Functions

We'll need to first determine what functions the shared libraries offer, and which of these the application is actually using. You may use a reverse engineering program like IDA if you wish, but binutils is sufficient for this one:

Execute the following:

```bash
nm -D example1 MyCustomCxxLib.so my_custom_c_lib.so | c++filt
```


`nm -D` shows us the imported and exported symbols of ELF objects. A `U` sits next to imported symbols, and a `T` sits next to exported function symbols.

### Note

If you usually use binutils nm without a `-D`, that sometimes works too, but technically this lists the debug symbols in an ELF object instead of the imported & exported symbols. ELFs may have had their debug symbols stripped, as is the case here.

`c++filt` is a program that un-mangles C++ names it sees. The net effect of C++ name mangling is that shared libraries reveal the argument types for C++ functions (e.g. `MyCustomCxxLib::process_data(char const*, char*)` here), but you don't get argument types for C functions (e.g. `my_custom_c_lib_process_data` here).

### Determining Harnessing Function Calls and Sequence

Decide which functions we'd like to call in our harness, and in which order. Typically, this is achieved by mild reverse-engineering of the application or libraries, to find example sequences of how the target functions are being called. This is relatively easy to do with [Ghidra](https://github.com/NationalSecurityAgency/ghidra). If you load and analyze the example1 binary, the decompilation window reveals the call order of the functions we're interested in.

A harness doesn't need to exactly imitate the application's usage of libraries, but there are a variety of issues you can run into when straying too far. In this case, blindly trying to fuzz `my_custom_c_lib_process_data()` alone will cause the library to issue a "bad format!" error, whereas the sequence of `MyCustomCxxLib::process_data()` and then `my_custom_c_lib_process_data()` will work fine. This particular case is somewhat artificial, but stereotypical of real-world harnessing efforts.

### Creating a Shared Library Harness

Create function declarations that allow you to link against the shared libraries. This application didn't ship with header files, but `nm` gives you most of the information you need to recreate them!

Directly from the `nm` output you saw before, you are able to infer:

```cpp
// Return type is unknown, because C++ name mangling doesn't include return types.
owner MyCustomCxxLib {
    ? process_data(const char*, char*);
}

// Return type and argument types are unknown, because it's a C function.
// In C++, C functions must be declared with extern "C".
// This lets C++ know to look for the unmangled name when linking.
extern "C" ? my_custom_c_lib_process_data(???);
```

The missing types here are int, void, and char *, int. You could determine this with trial and error, but if we load and analyze the libraries in Ghidra, we can look at the decompilation window to see the paramater/return types that we were unable to infer from the symbol demangling process above.

Lastly, see `harness.cxx`, or if you think you know what to do, try writing one on your own first. Ensure that you can compile, run, and fuzz this harness before moving on. Try to re-create `harness.cxx` on your own, to check your understanding.

**Tip:**

This strategy works best when using the same C++ compiler and platform as the target libraries were built with. For example, things may not work if you attempt to compile your harness with `g++` when the library was compiled with `clang++`. In particular, `g++`'s libstdc++ changed its implementation of `std::string` a few years ago, so older (still in use!) versions of `g++` toolchains are not binary compatible with recent versions. (Particularly for `g++`, solving this is sometimes as easy as switching between `-D_GLIBCXX_USE_CXX11_ABI=0` and `-D_GLIBCXX_USE_CXX11_ABI=1`.)
