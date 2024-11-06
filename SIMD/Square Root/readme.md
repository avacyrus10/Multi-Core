# Reciprocal Square Root Approximation Using AVX and Quake III Algorithm

This program demonstrates two methods for calculating the approximate reciprocal square root (1/sqrt(x)):

- AVX SIMD Intrinsics: Uses AVX instructions for vectorized parallel processing to calculate reciprocal square roots for an array of floating-point numbers.
- Quake III Fast Inverse Square Root: Implements the famous fast inverse square root algorithm used in the Quake III engine for individual numbers.

The program compares the output and execution time of both methods.
## How It Works

- AVX Reciprocal Square Root (avx_q_rsqrt): This function uses the AVX SIMD instruction _mm256_rsqrt_ps to calculate an approximation of the reciprocal square root for an array of 8 floating-point numbers. It applies one Newton-Raphson iteration to improve accuracy.

- Quake III Fast Inverse Square Root (q_rsqrt): This function implements the fast inverse square root algorithm used in the Quake III engine. It uses bit-level manipulation to achieve a fast approximation of the reciprocal square root.

- Performance Measurement: The execution time for both methods is measured and printed to compare their performance.

## Compilation

To compile the program, use the following command:

```bash
gcc -o rsqrt_approximation rsqrt_approximation.c -mavx2 -lm
```
This will produce an executable named rsqrt_approximation.

To run the program, simply execute:

```bash
./rsqrt_approximation
```


