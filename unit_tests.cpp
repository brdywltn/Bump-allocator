#include "bump.hpp"
#include <simpletest.h>

char const *groupAllocateAndDeallocate[] = {
    "BumpUp_AllocateAndDeallocate",
};

DEFINE_TEST_G(AllocateDealllocateSizesTest, BumpUp_AllocateAndDeallocate) {
    //Test 1: Allocate and deallocate various sizes of mem
    BumpUpAllocator<int> allocator1(100);
    int* x = allocator1.alloc(5);
    TEST_MESSAGE(x != nullptr, "Failed to allocate memory!");
    allocator1.dealloc(x);
}

int main() {

    bool pass = true; 

    for (auto group: groupAllocateAndDeallocate){
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }

    return pass ? 0 : 1;
}