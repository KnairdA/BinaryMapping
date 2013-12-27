# BinaryMapping

... is a simple collection of C++ templates which may be used to map binary structures into tuples. This is useful for many kinds of data serialization tasks.

A explanation of an earlier version of this template library can be found on my [blog](http://blog.kummerlaender.eu/artikel/mapping-binary-structures-as-tuples-using-template-metaprogramming).

## Current features:

- Support for any kind of flat structure that consists of integral types
- Full support for serialization in either big or little endianess
- Sliding mappings over buffers for fast iteration
- Integrated relative pointer template
- Builds on `std::tuple` and doesn't require any external libraries
- Header only library because of heavy usage of template metaprogramming
- Unit Tests based on GoogleTest

## Future goals:

- Modify `BinaryMapping` template to fullfill `std::random_access_iterator_tag`

## Requirements:

- [GoogleTest](http://code.google.com/p/googletest/) for tests
