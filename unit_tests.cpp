#include "bump.hpp"
#include <simpletest.h>

char const *groupAllocateAndDeallocate[] = {
    "BumpUp_AllocateAndDeallocate",
};

char const *groupAllocateToFullCapacity[] = {
    "BumpUp_AllocateToFullCapacity"
};

DEFINE_TEST_G(AllocateDealllocateSizesTest, BumpUp_AllocateAndDeallocate) {
    //Test 1: Allocate and deallocate various sizes of mem
    BumpUpAllocator<int> allocator1(100);
    int* x = allocator1.alloc(5);
    TEST_MESSAGE(x != nullptr, "Failed to allocate memory!");
    allocator1.dealloc(x);
}

DEFINE_TEST_G(AllocateToFullCapacityTest, BumpUp_AllocateToFullCapacity) {
    //Test 2: Allocate up to the full capacity of assigned mem
    BumpUpAllocator<char> allocator2(10);
    for (int i = 0; i < 3; i++){
        char* block = allocator2.alloc(3);
        TEST_MESSAGE(block != nullptr, "Memory allocation failed!");
    }
}

int main() {

    bool pass = true; 

    for (auto group: groupAllocateAndDeallocate){
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }

    for (auto group: groupAllocateToFullCapacity) {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }

    return pass ? 0 : 1;
}