#include <cstddef>
#include <iostream>

template <typename T>
class BumpAllocator {

private:
    char*   heap;
    char*   bumpPointer;
    size_t  allocationCounter;
    size_t  totalSize;

public:
    BumpAllocator(size_t initialSize){
        heap = new char[initialSize];
        bumpPointer = heap;
        allocationCounter = 0;
        totalSize = initialSize;
    }

    ~BumpAllocator(){
        delete[] heap;
    }

    T* alloc(size_t count){
        if (bumpPointer + count * sizeof(T) <= heap + totalSize) {
            T* allocation = reinterpret_cast<T*>(bumpPointer);
            bumpPointer += count * sizeof(T);
            allocationCounter++;
            return allocation;
        }
        else {
            std::cout << "Allocation failed, not enough memory." << std::endl;
            return nullptr;
        }
    }

    void dealloc(T* allocation){
        if (allocationCounter > 0) {
            allocationCounter--;
            if (allocationCounter == 0) {
                bumpPointer = heap;
            }
        }
    }

    char* getHeapStartAddress() const {
        return heap;
    }

    char* getCurrentPointerAddress() const {
        return bumpPointer;
    }
};