#include <cstddef>
#include <iostream>

template <typename T>
class BumpUpAllocator {
// An implementation of a BumpAllocator in C++
// which bumps the allocated memory spaces
// up through the heap

private:
    char*   heap; //start address
    char*   bumpPointer; //current address
    size_t  allocationCounter; // counter for allocations
    size_t  totalSize; //total size of allocated space

public:
    //Constructor
    //Creates space for the heap and initialises the private/public variables
    BumpUpAllocator(size_t initialSize){
        heap = new char[initialSize];
        bumpPointer = heap;
        allocationCounter = 0;
        totalSize = initialSize;
    }

    //Destructor
    ~BumpUpAllocator(){
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


//Bump down
template <typename T>
class BumpDownAllocator {
private:
    char* heap; //start address of the heap
    char* bumpPointer; //current position
    size_t allocationCounter; //counter for allocations
    size_t totalSize; //total size of allocated space

public:
    //constructor
    BumpDownAllocator(size_t initialSize) {
        heap = new char[initialSize];
        bumpPointer = heap + initialSize; //bumpPointer needs to start at the end of the heap
        allocationCounter = 0;
        totalSize = initialSize;
    }
        
    //destructor
    ~BumpDownAllocator() {
        delete[] heap;
    }
    //allocate
    T* alloc(size_t count) {
        //bumpPointer less amount of assigned mem must be greater than or same as heap, then go down
        if (bumpPointer - count * sizeof(T) >= heap){
            bumpPointer -= count * sizeof(T);
            T* allocation = reinterpret_cast<T*>(bumpPointer);
            allocationCounter++;
            return allocation;
        }
        // otherwise, no mem, fail
        else {
            std::cout << "Allocation failed. Not enough memory." << std::endl;
            return nullptr;
        }
    }

    //deallocate
    void dealloc(T* allocation){
        if (allocationCounter > 0) {
            allocationCounter--;
            if (allocationCounter == 0) {
                bumpPointer = heap + totalSize; //reset when allocations are freed
            }
        }
    }
};