#include <cstddef>
#include <iostream>

template <typename T>
class BumpAllocator {
// An implementation of a BumpAllocator in C++
//
//
//
//
private:
    char*   heap;
    char*   bumpPointer;
    size_t  allocationCounter;
    size_t  totalSize;

public:
    //Constructor
    BumpAllocator(size_t initialSize){
        heap = new char[initialSize];
        bumpPointer = heap;
        allocationCounter = 0;
        totalSize = initialSize;
    }

    //Destructor
    ~BumpAllocator(){
        delete[] heap;
    }
    

    //Allocate some memory
    T* alloc(size_t count){
        //Ensure that the next step is within the bounds of the initial memory allocation
        if (bumpPointer + count * sizeof(T) <= heap + totalSize) {
            //Add some extra memory at the end
            T* allocation = reinterpret_cast<T*>(bumpPointer);
            bumpPointer += count * sizeof(T);
            allocationCounter++;
            return allocation;
        }
        else {
            //We didn't have any space left, error
            std::cout << "Allocation failed, not enough memory." << std::endl;
            return nullptr;
        }
    }
    
    //Deallocate
    void dealloc(T* allocation){
        if (allocationCounter > 0) {
            allocationCounter--;
            if (allocationCounter == 0) {
                bumpPointer = heap;
            }
        }
    }

    //Return the heap, for sanity checking movement of mem
    char* getHeapStartAddress() const {
        return heap;
    }

    //Return the current pointer address, for sanity checking movement of mem
    char* getCurrentPointerAddress() const {
        return bumpPointer;
    }
};