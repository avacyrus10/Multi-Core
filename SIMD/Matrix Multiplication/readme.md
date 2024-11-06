# 16x16 Matrix Multiplication with SIMD and Non-SIMD Comparison

This program performs matrix multiplication on two 16x16 matrices using both SIMD (Single Instruction, Multiple Data) with AVX instructions and a standard non-SIMD method. It then compares the performance of both approaches and verifies the correctness of the results.
# How It Works

- SIMD Matrix Multiplication (matrix_mult): This function utilizes AVX instructions (_mm256) for parallel floating-point operations on the matrices. Loop unrolling is applied to optimize matrix multiplication.

- Non-SIMD Matrix Multiplication (matrix_mult_non_simd): This function performs the same matrix multiplication, but without any SIMD optimizations, using a straightforward triple nested loop.

- Result Comparison: After computing the matrix products, the results are compared with a tolerance to ensure the outputs from the SIMD and non-SIMD versions are identical.

- Execution Time Measurement: The program measures and prints the execution time for both the SIMD and non-SIMD matrix multiplication functions.

## Compilation

To compile the program, use the following command:

```bash
gcc -o matrix_mult matrix_mult.c -mavx2 -lm
```
This will produce an executable named matrix_mult.
Running the Program

To run the program, simply execute:

```bash
./matrix_mult
```


