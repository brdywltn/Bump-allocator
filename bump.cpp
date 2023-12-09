#include "bump.hpp"
#include <cstring>
#include <chrono>
#include <functional>

//Benchmark library
//need to include chrono and functional
template <typename Func, typename... Args>
//takes two args, Func and ...Args
double benchmark(Func func, Args&&... args) {
    //need a start
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    //and an end
    auto end = std::chrono::high_resolution_clock::now();
    //return end-start
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

void benchmarkBumpUp() {
    constexpr int numAllocations = 1000000;
    for (int i = 0; i < numAllocations; i++) {
       BumpUpAllocator<int> allocator(rand() % 100);
    }
}

void benchmarkBumpDown() {
    constexpr int numAllocations = 1000000;
    for (int i = 0; i < numAllocations; i++) {
       BumpDownAllocator<int> allocator(rand() % 100);
    }
}


int main() {
    // BumpUpAllocator<int> allocator(1000);

    // //check the starting address for sanity
    // std::cout << "Starting address of the heap: " << static_cast<void*>(allocator.getHeapStartAddress()) << std::endl;


    // int* intArray = allocator.alloc(5);
    // std::cout << "Current address of the heap: " << static_cast<void*>(allocator.getCurrentPointerAddress()) << "\n" << std::endl;
    // int* intArray2 = allocator.alloc(10);
    // std::cout << "Next address of the heap: " << static_cast<void*>(allocator.getCurrentPointerAddress()) << "\n" << std::endl;
    // if (intArray != nullptr) {
    //     for (int i = 0; i < 5; i++){
    //         intArray[i] = i * 10;
    //         std::cout << intArray[i] << " ";
            
    //     }
    // }

    // allocator.dealloc(intArray);

    // BumpDownAllocator<int> allocatorDown(1000);
    
    // //check the starting address for sanity
    // std::cout << "Starting address of the heap: " << static_cast<void*>(allocatorDown.getHeapStartAddress()) << std::endl;


    // int* intArray3 = allocatorDown.alloc(5);
    // std::cout << "Current address of the heap: " << static_cast<void*>(allocator.getCurrentPointerAddress()) << "\n" << std::endl;
    // int* intArray4 = allocatorDown.alloc(10);
    // std::cout << "Next address of the heap: " << static_cast<void*>(allocator.getCurrentPointerAddress()) << "\n" << std::endl;
    // if (intArray3 != nullptr) {
    //     for (int i = 0; i < 5; i++){
    //         intArray3[i] = i * 10;
    //         std::cout << intArray3[i] << " ";
            
    //     }
    // }

    // allocatorDown.dealloc(intArray3);

    //times
    double bumpUpTime = benchmark(benchmarkBumpUp);
    double bumpDownTime = benchmark(benchmarkBumpDown);

    //results please
    std::cout << "BumpUp allocator time: " << bumpUpTime << " microseconds\n";
    std::cout << "BumpDown allocator time: " << bumpDownTime << " microseconds\n";
    
    return 0;
}