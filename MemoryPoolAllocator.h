
#ifndef APC_MEMORYPOOLALLOCATOR_H
#define APC_MEMORYPOOLALLOCATOR_H

#include <cstddef>
#include <vector>

class MemoryPoolAllocator {
private:
    struct FreeBlock {
        FreeBlock* next;
    };

    FreeBlock* freeListHead;
    void* pool;
    size_t blockSize;
    size_t poolSize;

    std::vector<bool> blockAllocated; // track allocation status of each block

public:
    MemoryPoolAllocator(size_t blockSize, size_t numBlocks);
    ~MemoryPoolAllocator();

    void* allocate();
    void deallocate(void* pointer);

    const std::vector<bool>& getAllocationStatus() const { return blockAllocated; }
};

#endif //APC_MEMORYPOOLALLOCATOR_H
