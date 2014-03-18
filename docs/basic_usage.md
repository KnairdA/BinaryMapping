### Mapping structures into tuples

The core of the funtionality of this library lies within the `Tuple` template and its helper templates. A specialization of the `Tuple` template enables us to access the information contained within a buffer as if it was stored in a `std::tuple` instance. So if we want to map a structure consisting of three different integers on a buffer without caring about endianess we can instantiate the following specialization of the `Tuple` template:

```
BinaryMapping::dtl::Buffer buffer(70);

typedef BinaryMapping::PlainTuple<
    uint32_t,
    uint16_t,
    int8_t
>::type<uint8_t> TestTuple;

TestTuple tuple(buffer.front());
```

This `Tuple` instance points to the front of the buffer provided to its construtor and maps the first 4 bytes as a `uint32_t`, the next 2 bytes as `uint16_t` and the next single byte as `int8_t`. This leads to a total structure size of 7 bytes as specified by `TestTuple::size` which means that we can fit this structure 10 times into our 70 byte buffer. `PlainTuple` is a template alias which defines the endianess template argument as `UndefinedEndian` and leaves both the contained types and the memory base type to be specialized. 

*Hint: Note that while we are directly passing a pointer to the front of the Buffer instance this is only for demonstration purposes. Normally you would pass a Tuple type to the Container template which manages memory internally or can be constructed from raw memory pointers. Additionally it also takes away the responsibility of specializing the base memory type from the users of the library. If you want to know more about the libraries internal buffer management you may check out its [documentation](https://github.com/KnairdA/BinaryMapping/blob/master/docs/buffer.md).*

#### Endianess

If one wants to define the endianess one has to use the `Tuple` template directly and specify the endianess type as the first argument:

```
typedef BinaryMapping::Tuple<
    BinaryMapping::BigEndian,
    uint32_t,
    uint16_t,
    int8_t
>::type<uint8_t> TestTuple;

TestTuple tuple(buffer.front());
```

Endianess conversion is handled transparently in the background in this case. If the byte order is undefined the `Tuple` template offers additional `serialize` and `deserialize` template methods for manual endianess conversion.

#### Accessing the mapped structure

Similar to the standard libraries `std::tuple` all specializations of the `Tuple` template offer `set<Index>` and `get<Index>` template member methods to access the fields of the tuple.

```
tuple.set<0>(UINT32_MAX);
tuple.set<1>(UINT16_MAX);
tuple.set<2>(INT8_MAX);
```

The listing above sets each field of the tuple to its maximum value by directly modifying the underlying buffer. These values can be retrieved by value using the `get<Index>` template method:

```
uint32_t value1 = tuple.get<0>();
uint16_t value2 = tuple.get<1>();
int8_t   value3 = tuple.get<2>();
```

#### Directly accessing the underlying memory

If one wants to access tuple fields through a pointer instead of by-value one may use the `ptr<Index>` template member method of `Tuple`. The only difference between this method and `get<Index>` besides the obvious lack of endianess conversion is that it returns a direct pointer of the corresponding element type to the underlying memory with the correct offset applied instead of the element value.

#### By-value copy of a tuple

For extracting dereferenced copies of tuples the `Tuple` template offers the `value_type` operator overload. This operator returns a instance of the `std::tuple` template filled with all curent values of the tuple. The values can then be accessed in the same way as in all `std::tuple` instantiations.

```
TestTuple::value_type copy = tuple;
uint32_t value = std::get<0>(copy);
```

#### Populating tuples from matching std::tuple instances

Simmilar to the `value_type` operator overload provided for getting by-value copies of tuples as `std::tuple` instances the library offers a `operator=` overload to populate all values from a matching standard tuple.

```
tuple = TestTuple::value_type(1, 2, 3);
uint32_t value1 = tuple.get<0>(); // 1
uint16_t value2 = tuple.get<1>(); // 2
int8_t   value3 = tuple.get<2>(); // 3
```

#### Defining arbitrarily sized fields

If one needs to define fields in the mapped structure that do not confirm to the sizes defined by integral C++ language types one may use the `BitField` template offered by the library. This template type can be specialized with a bit size of type `size_t` and will instantiate an internal `std::array` of type `uint8_t` of the given size divided by eight. The only difference in usage of the `BitField` type compared to integral types is that it is unaware of endianess even if `Tuple` is specialized on a type of byte ordering. Additionally one may manipulate the underlying memory on the bit-level using methods such as `toggle(size_t)`. If one does not require bit-level access a apropriate `ByteField` type is available.

```
BinaryMapping::PlainTuple<
    uint16_t,
    BinaryMapping::BitField<24>,
    int16_t
>::type<uint8_t> BitFieldTestTuple;

BitFieldTestTuple tuple(buffer.front());

tuple.set<1>({1, 2, 3});
BinaryMapping::BitField<24> raw = tuple.get<1>();

raw.toggle(4);
```

### Using tuple containers and iterators

The `Tuple` template by itself can only be used to directly map areas of a buffer but it doesn't offer direct support for iterating over all tuples in a buffer. This functionality is abstracted in the `Container` and `Iterator` template classes. A instance of a specialization of the `Container` template transforms a given buffer into a virtual collection of tuples which can be accessed through common container member methods.

```
typedef BinaryMapping::Container<
    BinaryMapping::PlainTuple<
        uint32_t,
        uint16_t,
        int8_t
    >
> TestContainer;

// instantiate a container containing ten instances of our tuple type
TestContainer container(10);

// set second field of fifth tuple to its maximum value
container.at(5).set<1>(UINT16_MAX);

// get tuple instance located at the beginning of the container 
TestContainer::tuple_type tuple = container.front();
```

#### Iterator

Besides member methods returning instances of the `Tuple` template `Container` also offers methods which return tuple iterators. These iterators bind internal `Tuple` instances to `BufferIterator` iterators and provide all methods required to satisfy the `std::random_access_iterator_tag`. 

```
TestContainer::iterator_type iter = container.begin();
iter += 5;
 
// set the second field of the current tuple to its maximum value
(*iter).set<1>(UINT16_MAX);
```

Besides _normal_ iterator usage iterators can also be used in C++11 range-based for-loops:

```
// set the first field of all tuples in the container to one
for ( auto&& tuple : container ) {
    tuple.set<0>(1);
}
```

Note that the Container template offers apropriate const overloads of all member methods except `size()`. This means that const iterators are also available. If one calls the const overload of `element_type` access methods such as `at(size_t)` they will return a `value_type` instance.
