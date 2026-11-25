# Exam Assignment 11.11.2026

## Task 1
> Name some characteristics of the instructions sets: SSE, AVX(2) and AVX-512.

**SSE**: Streaming SIMD Extensions
- Years of launch: 1999-2009
- Vector length: 128 bits
- Number of registers: 16
- Register names: xmm0-xmm15

**AVX(2)**: Advanced Vector Extensions
- Years of launch: 2011, 2013
- Vector length: 256 bits
- Number of registers: 16 
- Register names: ymm0-ymm15

**AVX-512**:  Advanced Vector Extensions 512
- Years of launch: 2017
- Vector length: 512 bits
- Number of registers: 32
- Register names: zmm0-zmm31
    - ymm0-ymm31 are the lower halves of zmm0-zmm31
    - xmm0-xmm31 are the lower quarters of zmm0-zmm31

## Task 2
> How can memory aliasing affect performance?

Memory aliasing (or pointer aliasing) means that two pointers may point to the same memory location.
Per default a compiler is pessimistic and assumes that two pointers may point to the same memory location to avoid unsafe optimizations. Therefore a number of optimizations are not applied by the compiler, i.e. no performace optimizations are applied. Only when the compiler knows that referenced memory locations are unique, it can enable optimizations like vectorization.

```cpp
// restricted pointers signal a non-overlapping memory location to the compiler 
int *__restrict__ a;
int *__restrict__ b;
```

## Task 3
> What are the advantages of unit stride (stride-1) memory access compared to accessing memory with larger strides (for example, stride-8)?

Using unit stride memory access means that memory locations are accessed sequentially without skipping any memory locations. The advantage of unit stride memory access is that it has high cache efficiency since a complete cache line is loaded and all data elements in the cache line are used, therefore reducing cache misses. Another advantage is that the compiler can vectorize easily by using SIMD instructions. A single SIMD load can fetch multiple consecutive elements using one starting address, so there is no need to compute a separate address for each element.

## Task 4
> When would you prefer arranging records in memory as a Structure of Arrays?

A structure of arrays is preferred when performing operations on the same field across different instances as it allows for better data locality. 

**Array of Structures (AoS)**: At each index of the array, a complete structure is stored
```cpp
// Memory
a[0].x, a[0].y, a[0].z,
a[1].x, a[1].y, a[1].z,
a[2].x, a[2].y, a[2].z,
a[3].x, a[3].y, a[3].z
// Vector register
a[0].x, a[1].x, a[2].x, a[3].x
```

- Pro: Good memory locality when accessing multiple fields of the same instance --> fields are consecutive
- Con: Accessing same field accross different instances is not cache friendly --> fields are not consecutive

**Structure of Arrays (SoA)**: Single structure where each field is an array of values
```cpp
// Memory
a.x[0], a.x[1], a.x[2], a.x[3],
a.y[0], a.y[1], a.y[2], a.y[3],
a.z[0], a.z[1], a.z[2], a.z[3]
// Vector register
a.x[0], a.x[1], a.x[2], a.x[3]
```

- Pro: Good memory locality when accessing the same field across different instances --> fields are consecutive
    - Useful for operations like `min`, `max`, `sum`, `average`, 
- Con Accessing multiple fields of the same instance is not cache friendly --> fields are not consecutive

## Task 5
> Further reading (optional): [Improving Performance with SIMD Intrinsics](https://real.mtak.hu/163819/1/1388_doi2.pdf).