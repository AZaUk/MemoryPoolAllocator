# Dynamic Memory Allocation in C++

## Introduction

Dynamic memory allocation in C++ is very vital, it makes programs use memory efficiently during ***runtime***. The `::operator new` in C++ and `malloc` in C are usually used for this purpose. Here, in this markdown, we will use more words to describe how dynamic memory allocation works, its common algorithms, advantages, and pitfalls.

### ::operator new

In `C++` we use `::operator new` to allocate memory dynamically on the heap. We usually use it with classes when creating objects. If allocation fails, it throws a `std::bad_alloc` exception, unless we explicitly ask it not to using `nothrow`.

### malloc

In `C` we use `malloc` (memory allocation) function to allocate a block of memory. It returns a pointer to the beginning of it. If compared to `::operator new`, `malloc` doesn't call constructors.

## Common Algorithms for Dynamic Memory Allocation

Fist algorithm is called **First Fit**. It scans memory, from its beginning, and allocates the first block that is big enough for your case. It is pretty simple and fast for small allocations, however, it can lead to fragmentation over time. 

> See what fragmentation is [here](https://en.wikipedia.org/wiki/Fragmentation_(computing))

Second algorithm in our list is called **Best Fit**. It fully scans the memory and finds the smallest block that fits your requirements. In this case, fragmentation risk is reduced, but it is, of course much slower, as it scans all blocks.

Third algorithm that we will explain today is **Worst Fit**. It allocates the largest available block. This can be fine when you need a lot of memory, and it leaves smaller blocks for smaller allocations, but if you use it inefficiently, it will create large unusable segments over time.

Fourth algorithm in this selection is **Next Fit**. It is very similar to the *First Fit*, it scans memory from beginning, and allocates next block that is big enough. It can lead to better performace than *First Fit*, but still inherits fragmentation issues, and can take more time to scan block.

Last algorithm in our list is **Buddy System**. It splits memory in halves, to give you the best fit possible. It is decently fast and efficient for allocating and deallocating memory of different sizes. However, it still has fragmentation issues and is much harder to implement.

> If you would like to make a more thorough research and read more text, here are the links that describe algorithms in more words - [First Fit Allocation](https://www.javatpoint.com/first-fit-algorithm-in-c), [Best Fit Allocation](https://www.thecrazyprogrammer.com/2017/01/best-fit-algorithm-c-c.html), [Worst Fit Allocation](https://prepinsta.com/operating-systems/page-replacement-algorithms/worst-fit/), [Next Fit Allocation](https://www.codingalpha.com/next-fit-algorithm-c-program/), [Buddy Memory Allocation](https://en.wikipedia.org/wiki/Buddy_memory_allocation)

## Advantages of Dynamic Memory Allocation

First of all, it allows you to allocate memory at runtime, which is very flexible solution. Secondly, it gives you more control over memory management in the program. And of course, depending on your implementation, it can be very efficient, as it might allocate only what you need in memory.

## Pitfalls of Dynamic Memory Allocation

Most common disadvantages are memory leaks, fragmentation, complex implementation and overhead. If you forget to deallocate memory, or improperly allocate it, you will face memory leak, and your device will start lagging, making it unusable (which happened to us while implementing custom memory memory allocator).

> Some usefull links - 
> - [Fragmentation](https://en.wikipedia.org/wiki/Fragmentation_(computing))
> - [Memory Leak](https://en.wikipedia.org/wiki/Memory_leak)
> - [Overhead](https://medium.com/@sim30217/overhead-a2d60b5de76e)
> - [Difference between Static and Dynamic memory allocation](https://byjus.com/gate/difference-between-static-and-dynamic-memory-allocation-in-c/)
> *Dynamic memory allocation is preferred in the linked list.

## Conclusion

Well, in conclusion, we would like to say that it is pretty cruicial to know about memory allocation, how it works, how to do it, if you want to create proffesional apps. It is also vital to choose proper algorithm for your program, to not occupy extra space, to not cause memory leaks and fragmentations.

## Implementation of Custom Dynamic Memory Allocator

### `<cstddef>`

We import `<cstddef>` to be able to use `size_t` *(unsigned integer type returned by the sizeof operator )* in our project. If you would like to read about, you can do it [here](https://en.cppreference.com/w/cpp/header/cstddef)

### `<cstdlib>`

We import `<cstdlib>` in MemoryPoolAllocator.cpp to use `malloc` (of course, we also use malloc under the hood) and `free` to free the allocated memory afterwards. And you can, of course, read about `<cstdlib>` [here](https://en.cppreference.com/w/cpp/header/cstdlib)

#### static_cast and reinterpret_cast

We also use `static_cast` and `reinterpret_cast` in our implementation. `static_cast` is used to convert void pointer, which malloc gave us, into a pointer of type FreeBlock. `reinterpret_cast` is a more advanced one, and it can converrt any pointer type to any other pointer type. In our case we use it to calculate memory address of the next block.

### First test

First test was successful, this is the output we received `address is: 0x124808800 address is: 0x124808800`, which means that allocation works as expected.

And here comes the first bug. We forgot to deallocate memory during runtime. This caused lagging on the machine and unusability of os. be careful.

### Testing of allocation and deallocation

After writing some tests in `main.cpp` file, this is the output
```
Allocated first bloack at: 0x14a808800
Allocated second block at: 0x14a808900
let's see how ptr1 looks like now: 0x14a808800
and after the deallocation: 0x14a808800
And allocated third block at: 0x14a808800
ptr1: 0x14a808800
ptr2: 0x14a808900
ptr3: 0x14a808800
```

As we can see, it works as expected, and third block is allocated on the place of the first one, which was deallocated.

### More thorough testing

We expanded tests to show status of each block, after it was allocated or deallocated.

### Timings and Comparison

We also decided to measure how much time our allocator takes to allocate and deallocate memory, and to compare it with standard new/delete memory allocation in C++. We used `chrono` and it's `high_resolution_clock`, as well as `duration_cast` to measure how much time it takes. The results are pleasing, our custom memory allocator is faster then default one. Sometimes it's much faster, sometimes just a little, but here are the different tests:
```
Custom Allocator - Allocation Time: 83 nanoseconds
Custom Allocator - Deallocation Time: 125 nanoseconds
Standard New - Allocation Time: 125 nanoseconds
Standard Delete - Deallocation Time: 125 nanoseconds
```
```
Custom Allocator - Allocation Time: 167 nanoseconds
Custom Allocator - Deallocation Time: 0 nanoseconds
Standard New - Allocation Time: 3292 nanoseconds
Standard Delete - Deallocation Time: 125 nanoseconds
```
```
Custom Allocator - Allocation Time: 291 nanoseconds
Custom Allocator - Deallocation Time: 41 nanoseconds
Standard New - Allocation Time: 3125 nanoseconds
Standard Delete - Deallocation Time: 208 nanoseconds
```

## Alternatives

There is, of course, a lot of other ways to allocate memory in C++. We will show most popular ones

### `new` and `delete`

While this is a totally valid option, and it's used a lot in C++, you saw (just above) that it is pretty slow. It is not intended for small objects and quick allocation/deallocation of memory. It also has overhead and fragmentation issues.

### Smart Pointers `std::unique_ptr`

It has automated memory management and minimizes memory leaks, but it still has overhead and memory fragmentation issues.

### Memory Allocation functions `malloc`, `realloc`

It is a pretty low-level memory management (and we use it under the hood), but they do not automatically call constructors and destructors, and still have fragmentation and overhead issues.

### Custom Allocators

These are usually pretty complex to implement. In our case, it's just a simple pool allocator, which is efficient for fixed-size objects, and it is fast, also it has minimized risk of fragmentation and overhead.

## List of resources

> [First Fit Allocation](https://www.javatpoint.com/first-fit-algorithm-in-c)<br>
> [Best Fit Allocation](https://www.thecrazyprogrammer.com/2017/01/best-fit-algorithm-c-c.html)<br>
> [Worst Fit Allocation](https://prepinsta.com/operating-systems/page-replacement-algorithms/worst-fit/)<br>
> [Next Fit Allocation](https://www.codingalpha.com/next-fit-algorithm-c-program/)<br>
> [Buddy Memory Allocation](https://en.wikipedia.org/wiki/Buddy_memory_allocation)<br>
> [Fragmentation](https://en.wikipedia.org/wiki/Fragmentation_(computing))<br>
> [Memory Leak](https://en.wikipedia.org/wiki/Memory_leak)<br>
> [Overhead](https://medium.com/@sim30217/overhead-a2d60b5de76e)<br>
> [Difference between Static and Dynamic memory allocation](https://byjus.com/gate/difference-between-static-and-dynamic-memory-allocation-in-c/)<br>
> [`<cstddef>` (link)](https://en.cppreference.com/w/cpp/header/cstddef)<br>
> [`<cstdlib>` (link)](https://en.cppreference.com/w/cpp/header/cstdlib)