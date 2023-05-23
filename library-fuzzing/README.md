# Harnessing with Shared Libraries

In this lesson, we'll walk you through how to fuzz C++ applications that may not seem immediately amenable for fuzzing but whose shared libraries can be fuzzed by linking a source C++ harness against the binary.

**Estimated Time:** 10 minutes

## Objectives

By the end of this lesson, you will be able to:

- Define what a shared library is.
- Articulate the difference between harnessing libraries vs. applications.
- Explain how binary-only harnessing works.
- Walk through an example shared library harness.

## Shared Libraries

A shared library...

- Is a .so file on Linux, and a .dll on Windows.
- Contains compiled code and associated data.
- Can be shared or used among different programs.

The original purpose of shared libraries is to save disk space by sharing compiled code between multiple binary programs. When a software library is compiled as a shared library object, programs can load this library instead of containing their own copy of the library's code.

**Note:**
Programs loading a library make a virtual in-memory copy of that library. Therefore, multiple programs using the same shared library do not interfere with each other.

Shared libraries can also be used to provide software libraries in a pre-compiled form to avoid including their full source. In this use case, header files are provided as well, which tell the source compiler how to link against the shared library. There is also program metadata within shared libraries themselves that contain linking information (most notably function name symbols).

Modern applications are often delivered in a package consisting of one or more program executables, and multiple shared libraries that the programs depend upon. In this use case, the shared libraries may not actually be intended to be shared among multiple programs, or have new programs linked against them. But it remains technically possible by writing harnesses for shared libraries. Let's see how this is done!

## Harnessing Libraries vs Applications

In general, when harnessing any library-like component of an application (not just shared libraries), consider the following:

- A harness for a library is essentially an alternate application written with that library. Even though this alternate application can be simple, creating it is often more work than fuzzing an existing application.
- The way an application uses (or misuses) a library may differ from the way a harness uses that library. A harness that does not adequately imitate the application will miss or encounter different bugs.
- A library harness has no ability to find bugs in application code outside of that library.

There are two main reasons you may wish to harness a library, as opposed to an application:

1. The library may be easier to harness than the application. For example, an HTML parser is relatively easy to harness, and a web browser is not.
2. Potentially improving the speed or quality of fuzzing: At the library level, your harness can have a more fine-grained ability to skip slow or uninteresting parts of the software logic, resulting in a faster harness that finds more bugs.

Typically speaking, it's best to try to harness a whole application first, along with any library components you believe are particularly easy and particularly buggy (for example, parsers or protocol-processing code). Additional library components should be harnessed only if the whole-application harness doesn't seem to be producing adequate coverage for that component.

## Binary-only Harnessing

Security experts often need to harness a shared library that is provided without source. This tutorial is aimed at exploring custom shared libraries shipped with an application for which source is not available.

If, for example, you know that an application uses an open source library, it's better to acquire the source (preferably for the same version as the application uses) and use source-harnessing techniques on that.

