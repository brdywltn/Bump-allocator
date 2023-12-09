# Worksheet Two - Brody Wilton

## Memory Management: Bump Allocators

This is an implementation of a bump allocator, a simple memory management technique that allocates memory in contiguous chunks up to a user defined limit. Within this repo are two implementations of the bump allocator, one which bumps up through the heap, and one which bumps down through the heap. There is also a small benchmarking suite which I've used to show the time difference between the two implementations of the bump allocator.

### Running the code

To compile the code, simply run the following command while you're within the root folder of the directory:

``` clang++ -std=c++17 bump.cpp -o bump ```

And then to run the compiled code, run the following command while in the root folder of the directory

``` ./bump ```

### Running the unit tests

To compule the unit tests, simply run the following command while you're within the root folder of the directory:

``` clang++ -std=c++17 -I./simpletest -o test unit_tests.cpp simpletest/simpletest.cpp ```

And then to run the compiled unit test code, run the following command while in the root folder of the directory

``` ./test ```