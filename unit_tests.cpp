#include "bump.hpp"
#include <simpletest.h>

char const *groupAllocateAndDeallocate[] = {
    "BumpUp_AllocateAndDeallocate",
};

char const *groupAllocateToFullCapacity[] = {
    "BumpUp_AllocateToFullCapacity"
};

char const *groupAllocateDeallocateLoop[] = {
    "BumpUp_AllocateDeallocateLoop",
};

DEFINE_TEST_G(AllocateDealllocateSizesTest, BumpUp_AllocateAndDeallocate) {
    //Test 1: Allocate and deallocate various sizes of mem
    BumpUpAllocator<int> allocator1(100);
    int* x = allocator1.alloc(5);
    TEST_MESSAGE(x != nullptr, "Failed to allocate memory!");
    allocator1.dealloc(x);

    BumpUpAllocator<double> allocator2(50);
    double* y = allocator2.alloc(10);
    TEST_MESSAGE(y != nullptr, "Failed to allocate memory!");
    allocator2.dealloc(y);
}

DEFINE_TEST_G(AllocateToFullCapacityTest, BumpUp_AllocateToFullCapacity) {
    //Test 2: Allocate up to the full capacity of assigned mem
    BumpUpAllocator<char> allocator3(10);
    for (int i = 0; i < 3; i++){
        char* block = allocator3.alloc(3);
        TEST_MESSAGE(block != nullptr, "Memory allocation failed!");
    }
}

DEFINE_TEST_G(AllocateDeallocateLoopTest, BumpUp_AllocateDeallocateLoop){
    //Test 3: Allocate and deallocate in a loop

    BumpUpAllocator<float> allocator4(30);
    for (int i = 0; i < 5; i++){
        float* block = allocator4.alloc(4);
        TEST_MESSAGE(block != nullptr, "Failed to allocate memory");
        allocator4.dealloc(block);
    }
}

int main() {

    bool pass = true; 

    //Execute tests in the first group
    for (auto group: groupAllocateAndDeallocate){
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }

    //Execute tests in the second group
    for (auto group: groupAllocateToFullCapacity) {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }

    //Execute tests in the third group
    for (auto group: groupAllocateDeallocateLoop) {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }

    return pass ? 0 : 1;
}