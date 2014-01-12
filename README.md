# BinaryMapping

... is a simple collection of C++ templates which may be used to map binary structures into tuples. This is useful for many kinds of data serialization tasks.

A explanation of an earlier version of this template library can be found on my [blog](http://blog.kummerlaender.eu/artikel/mapping-binary-structures-as-tuples-using-template-metaprogramming).

Basic usage of this library is documented in the [wiki](https://github.com/KnairdA/BinaryMapping/wiki/Basic-Usage).

## Current features:

- Support for any kind of flat structure that consists of integral types
- Full support for serialization in either big or little endianess
- Container and Iterator templates for fast traversal of collections of tuples
- Integrated relative pointer template
- Builds on `std::tuple` and doesn't require any external libraries
- Header only library because of heavy usage of template metaprogramming
- Unit Tests based on GoogleTest
- MIT license

## Requirements:

- Current version of GCC or Clang C++ compiler with full support for C++11 (tested in g++ >= 4.8.2 and clang++ >= 3.3)
- GNU libraries _endian.h_ for endianess conversion support
- [GoogleTest](http://code.google.com/p/googletest/) for tests
