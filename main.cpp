#include "MemoryPoolAllocator.h"
#include <iostream>
#include <vector>


using Clock = std::chrono::high_resolution_clock;

void printMemoryState(const MemoryPoolAllocator& allocator, const std::string& phase) {
    std::cout << "Memory State after " << phase << ":\n";
    const auto& status = allocator.getAllocationStatus();
    for (size_t i = 0; i < status.size(); ++i) {
        std::cout << "Block " << i << ": " << (status[i] ? "Allocated" : "Free") << std::endl;
    }
}


int main() {
    const size_t blockSize = 256;
    const size_t numBlocks = 10;
    MemoryPoolAllocator allocator(blockSize, numBlocks);

    printMemoryState(allocator, "Initialization");

    // Test 1 - allocate first block
    void* ptr1 = allocator.allocate();
    std::cout << "Allocated first bloack at: " << ptr1 << std::endl;
    printMemoryState(allocator, "After Block 1 allocation");

    // Test 2 - allocate second block
    void* ptr2 = allocator.allocate();
    std::cout << "Allocated second block at: " << ptr2 << std::endl;
    printMemoryState(allocator, "After Block 2 allocation");

    // Test 3 - deallocate first block
    std::cout << "let's see how ptr1 looks like now: " << ptr1 << std::endl;
    printMemoryState(allocator, "Before Block 1 deallocation");
    allocator.deallocate(ptr1);
    std::cout << "and after the deallocation: " << ptr1 << std::endl;
    printMemoryState(allocator, "After Block 1 deallocation");

    // Test 4 - allocate third block (this shoyld allocate on the same spot as first block, as it was deallocated)
    void* ptr3 = allocator.allocate();
    std::cout << "And allocated third block at: " << ptr3 << std::endl;
    printMemoryState(allocator, "After Block 3 allocation");

    // Now let's not forget to deallocate everything
    allocator.deallocate(ptr2);
    allocator.deallocate(ptr3);

    // And jsut curios how all of them will look like after
    std::cout << "ptr1: " << ptr1 << std::endl;
    std::cout << "ptr2: " << ptr2 << std::endl;
    std::cout << "ptr3: " << ptr3 << std::endl;

    printMemoryState(allocator, "Final deallocation");



    auto start = Clock::now();
    void* ptr = allocator.allocate();
    auto end = Clock::now();
    std::cout << "Custom Allocator - Allocation Time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
              << " nanoseconds" << std::endl;

    start = Clock::now();
    allocator.deallocate(ptr);
    end = Clock::now();
    std::cout << "Custom Allocator - Deallocation Time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
              << " nanoseconds" << std::endl;

    start = Clock::now();
    char* standardPtr = new char[blockSize];
    end = Clock::now();
    std::cout << "Standard New - Allocation Time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
              << " nanoseconds" << std::endl;

    start = Clock::now();
    delete[] standardPtr;
    end = Clock::now();
    std::cout << "Standard Delete - Deallocation Time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
              << " nanoseconds" << std::endl;

    return 0;
}