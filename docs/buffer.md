### Internal buffer management

Source: [src/detail/io/](https://github.com/KnairdA/BinaryMapping/tree/master/src/detail/io)

All data which one wishes to access using the BinaryMapping templates is internally wrapped in a instance of the `dtl::Buffer` class. This class currently offers two constructor overloads to satisfy different ways of managing memory. For the purpose of this introduction we will use the constructor with the signature `Buffer(size_t)` which offers internal self-allocation and scope-guarding of the quantity of memory in bytes specified by the `size_t` argument.

```
BinaryMapping::dtl::Buffer buffer(70);
```

This newly created `Buffer` instance allocated 70 bytes of memory and will automatically free it at the end of its lifetime. We can now make use of the various methods `Buffer` offers to access the underlying memory. The methods are modeled after common methods offered by the standard containers, so we can for example get a pointer to the beginning of the memory by calling `buffer.front()`. A special aspect of this container are its template methods which offer access to its memory in specified intervals. 

```
// amount of elements with size 2 which fit into the container
size_t count = buffer.size<2>();
```

Besides direct access of the underlying memory `Buffer` also offers  iterators to its content. These iterators may be bound to `BinaryMapping::Tuple` template instances or simply be used as a convenient way to iterate over the memory.

```
// get Buffer::iterator<uint8_t, sizeof(uint32_t)> instance to the beginning of the buffer
auto iter = buffer.begin<sizeof(uint32_t)>();
```

As all iterators of the BinaryMapping library `Buffer::iterator<Size>` satisfies the requirements of `std::random_access_iterator_tag` and because of that can be used in the same way we are used to from iterators provied by the standard library. Note that all member methods but the size methods have appropriate const overloads.
