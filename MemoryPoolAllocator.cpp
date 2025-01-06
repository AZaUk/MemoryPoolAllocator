#include "MemoryPoolAllocator.h"
#include <cstdlib>


MemoryPoolAllocator::MemoryPoolAllocator(size_t blockSize, size_t numBlocks) : blockAllocated(numBlocks, false) { // initialize all blocks as not allocated
    this->blockSize = blockSize;
    this->poolSize = blockSize * numBlocks;
    this->pool = malloc(this->poolSize);
    this->freeListHead = static_cast<FreeBlock*>(this->pool);

    FreeBlock* current = freeListHead;
    for (size_t i = 0; i < numBlocks - 1; ++i) {
        current->next = reinterpret_cast<FreeBlock*>(
                reinterpret_cast<char*>(current) + blockSize);
        current = current->next;
    }
    current->next = nullptr;
}

MemoryPoolAllocator::~MemoryPoolAllocator() {
    free(this->pool);
}

void* MemoryPoolAllocator::allocate() {
    if (freeListHead == nullptr) return nullptr; // Pool is full

    FreeBlock* block = freeListHead;
    freeListHead = freeListHead->next;

    size_t blockIndex = (reinterpret_cast<char*>(block) - static_cast<char*>(pool)) / blockSize; // block is allocated
    blockAllocated[blockIndex] = true;

    return block;
}

void MemoryPoolAllocator::deallocate(void* pointer) {
    FreeBlock* block = static_cast<FreeBlock*>(pointer);
    block->next = freeListHead;
    freeListHead = block;

    size_t blockIndex = (static_cast<char*>(pointer) - static_cast<char*>(pool)) / blockSize; // block is free
    blockAllocated[blockIndex] = false;
}