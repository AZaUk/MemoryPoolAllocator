
# MemoryPoolAllocator

A high-performance memory pool allocator designed for efficient memory management in C++ projects.

## Features

- **Fast Allocation/Deallocation**: Reduces memory fragmentation and improves performance by reusing memory blocks.
- **Custom Pool Sizes**: Supports pools tailored to specific object sizes.
- **Thread-Safe**: Offers thread-safe allocation for concurrent applications (if applicable).
- **Lightweight**: Minimal overhead and highly configurable.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [API Documentation](#api-documentation)
- [Contributing](#contributing)
- [License](#license)

---

## Installation

Clone the repository and include the allocator in your project:

```bash
git clone https://github.com/AZaUk/MemoryPoolAllocator.git
```

Then include the necessary header files in your project:

```cpp
#include "MemoryPoolAllocator.h"
```

Alternatively, copy the relevant files into your project directory.

---

## Usage

Here’s a quick example of how to use the MemoryPoolAllocator:

```cpp
#include "MemoryPoolAllocator.h"

int main() {
    // Create a memory pool
    const size_t blockSize = 256;
    const size_t numBlocks = 10;
    
    MemoryPoolAllocator allocator(blockSize, numBlocks);

    // Allocate an object from the pool
    void* ptr1 = allocator.allocate();

    // Deallocate the object
    allocator.deallocate(ptr1);

    return 0;
}
```

---

## Examples & Test

Additional examples can be found in the [main.cpp](main.cpp/) file. These examples cover:

1. Basic usage with simple types.
2. Tests and timings

---

## API Documentation

### `MemoryPoolAllocator`

#### Constructor

```cpp
MemoryPoolAllocator(size_t blockSize, size_t numBlocks);
```

- **blockSize**: The size of a block the pool can preallocate.
- **numBlocks**: The number of blocks the pool can preallocate.

#### Methods

- **`T* allocate()`**  
  Allocates memory for a single object of type `T`.

- **`void deallocate(T* ptr)`**  
  Releases the memory back to the pool.

- **`size_t getAllocationStatus()`**

  Returns the number of available slots in the pool.

---

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a feature branch:
    ```bash
    git checkout -b feature/your-feature
    ```
3. Commit your changes: 
    ```bash
    git commit -m "Add some feature"
    ```
4. Push to the branch: 
    ```bash
    git push origin feature/your-feature.
    ```
5. Open a pull request.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Acknowledgments

Special thanks to all contributors and developers who made this project possible.
