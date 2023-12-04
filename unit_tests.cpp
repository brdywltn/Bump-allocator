#include "bump.hpp"
#include <simpletest.h>

char const *groups[] = {
    "Bump",
};

DEFINE_TEST_GROUP(BumpAllocatorTests, Bump)
{
    //Test 1: Allocate and deallocate various sizes
    TEST_MESSAGE("Test 1: Allocate and deallocate various mem sizes")

    BumpAllocator<int> allocator1(100);
    int* x = allocator1.alloc(5);
    TEST_MESSAGE(x != nullptr, "Failed to allocate memory");
    allocator1.dealloc(x);

    BumpAllocator<double> allocator2(50);
    double* y = allocator2.alloc(10);
    TEST_MESSAGE(y != nullptr, "Failed to allocate memory");
    allocator2.dealloc(y);

    

}