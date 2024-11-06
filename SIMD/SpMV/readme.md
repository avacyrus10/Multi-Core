# Sparse Matrix-Vector Multiplication (SpMV)

This project implements and compares various optimizations for Sparse Matrix-Vector Multiplication (SpMV). It supports four different implementations:

- Dense Matrix-Vector Multiplication (Baseline): A standard matrix-vector multiplication for dense matrices.
- Sparse Matrix-Vector Multiplication (Single-threaded): Uses the Compressed Sparse Row (CSR) format to optimize multiplication with sparse matrices.
- Sparse Matrix-Vector Multiplication (Multi-threaded): Uses OpenMP to parallelize SpMV across multiple threads.
- Sparse Matrix-Vector Multiplication (SIMD): Optimizes SpMV using AVX SIMD instructions for vectorized processing.

## How It Works
1. **Dense Matrix-Vector Multiplication**
    This serves as the baseline, performing a straightforward matrix-vector multiplication on a dense matrix, processing all non-zero elements without any optimizations.
2. **Sparse Matrix-Vector Multiplication (Single-threaded)**
 This implementation uses the CSR (Compressed Sparse Row) format to store only the non-zero elements of a sparse matrix, significantly reducing memory usage and improving computation time by skipping zero entries.
3. **Sparse Matrix-Vector Multiplication (Multi-threaded)**
This version uses OpenMP to parallelize the computation by distributing the row-wise operations across multiple threads, providing a performance boost by leveraging multiple CPU cores.
4. **Sparse Matrix-Vector Multiplication (SIMD with AVX)**
This version uses AVX SIMD (Single Instruction, Multiple Data) instructions to perform vectorized floating-point operations, speeding up the computation by processing multiple values in parallel within a single CPU instruction.
## How to Build and Run
1. Generate Input Data

Before running the program, you need to generate a random matrix and vector using the input_gen.c file. This will generate a matrix.txt and vector.txt file for use in the matrix-vector multiplication.

```bash
make generate_input
```

This will create:

    matrix.txt: A randomly generated 1000x1000 matrix.
    vector.txt: A randomly generated vector of size 1000.

2. Compile and Run All Implementations

To compile the code and run all four implementations, use the following command:

```bash
make run
```
This will:
- Run and compile all implementations (Dense, Sparse, Multi-threaded, SIMD).
- Measure and print the execution time for each implementation.

## Sample Output

The output will show the time taken for each implementation:

```bash
Dense Matrix-Vector Multiplication Done. Time: 0.000546 seconds
Sparse Matrix-Vector Multiplication (Single-threaded) Done. Time: 0.000577 seconds
Sparse Matrix-Vector Multiplication (Multi-threaded) Done. Time: 0.000569 seconds
Sparse Matrix-Vector Multiplication (SIMD) Done. Time: 0.000365 seconds
```

## Requirements

- GCC: The project uses GCC for compilation. Ensure that your GCC version supports AVX instructions (-mavx2).
- OpenMP: OpenMP is required for the multi-threaded version (-fopenmp).

## Conclusion

This project showcases how optimizing matrix-vector multiplication using sparse matrix formats, multi-threading, and SIMD instructions can significantly boost performance. You can easily compare the execution times of different implementations and see the impact of each optimization technique
