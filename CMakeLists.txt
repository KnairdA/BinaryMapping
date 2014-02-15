cmake_minimum_required(VERSION 2.8)
project(BinaryMapping)

set(
	CMAKE_CXX_FLAGS
	"-std=c++11 -W -Wall -Wextra -Winline -pedantic"
)

include_directories(
	src/
	src/io
	src/tuple
	src/endianess
)

add_executable(
	test
	test.cc
	tests/buffer.cc
	tests/tuple.cc
	tests/endianess.cc
	tests/container.cc
	tests/bitmap.cc
)

target_link_libraries(
	test
	gtest
)

add_custom_command(
	TARGET test
	POST_BUILD COMMAND ./test
)
