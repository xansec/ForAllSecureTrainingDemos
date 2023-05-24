## Objects Change Things

**File:** [example2.tgz](./example2.tgz)

`example2` is a more complex target, but we'll follow the same general process as we did for `example1` to harness it: reverse engineer the binaries to make working header files, write a harness in C++ that exercises the library (in a way similar to how we see the library being used), and then compile the harness and link it to the library.

When C++ objects are involved, this process requires more work and a greater attention to detail. Functions you'll want to harness may take C++ objects as parameters, which requires your harness to create these C++ objects beforehand. Furthermore, creating and properly initializing C++ objects requires having a correct-enough class definition for the object.

Quick refresher on C++ classes:

```C++
class  MyClass  /* : public OptionalBaseClass */  {
public:  // <- for harnessing purposes, just set everything public.
  int  member1;
  int  member2;
  // ^ the size of a class is the size of a struct holding all of its
  // non-static data members (plus a vtable pointer, if the class or a
  // parent class has any virtual member functions. But, that happens
  // automatically).

  // Constructors. From a reverse-engineering perspective, constructors
  // are just (non-virtual) member functions that get called to initialize
  // classes.
  MyClass(int,  float);
  MyClass(char  *);

  // Member functions. From a reverse-engineering perspective, they're just
  // functions that take an implicit first argument, known as "this", which
  // is a pointer to a struct containing the object's data members.
  int  do_something(int);
  void  do_something_else(float);
}
```


**Tip:** You can read more about the syntax of [C++ class definitions](https://en.cppreference.com/w/cpp/language/class), but most of the other things you can do in a class definition are irrelevant to harnessing and reverse engineering.)

Three things matter when creating a "correct-enough" class definition:

1.  Function declarations for member functions that you intend to call (including constructors).
2.  The size of the class.
3.  If the class has any virtual methods (including destructors), or any parent classes with virtual methods, you need to include all of those (and possibly re-create the inheritance hierarchy). We'll stay away from virtual methods in this tutorial.

If a program used the example class above, a reverse-engineered definition of the class for use in a harness might look like:

```C++
class  MyClass  {
public:
  char  data[8];  // two ints.

  // No need to represent constructors and member functions that the harness
  // doesn't care about using.
  MyClass(char  *);
  int  do_something(int);
}
```


To study this example, go through the same process enumerated for the first example. Study `harness.cxx`, and the source files for `example2` and `ex2lib.so`. To check your understanding, close `harness.cxx` and attempt to recreate it using only the binaries (of course, feel free to cheat with some of the `example2` and `ex2lib.so` source to ease the reverse-engineering process).
