#include "bump.hpp"
#include <cstring>

int main() {
    BumpUpAllocator<int> allocator(1000);

    //check the starting address for sanity
    std::cout << "Starting address of the heap: " << static_cast<void*>(allocator.getHeapStartAddress()) << std::endl;


    int* intArray = allocator.alloc(5);
    std::cout << "Current address of the heap: " << static_cast<void*>(allocator.getCurrentPointerAddress()) << "\n" << std::endl;
    int* intArray2 = allocator.alloc(10);
    std::cout << "Next address of the heap: " << static_cast<void*>(allocator.getCurrentPointerAddress()) << "\n" << std::endl;
    if (intArray != nullptr) {
        for (int i = 0; i < 5; i++){
            intArray[i] = i * 10;
            std::cout << intArray[i] << " ";
            
        }
        
        std::cout << std::endl;
    }

    allocator.dealloc(intArray);
    
    return 0;
}