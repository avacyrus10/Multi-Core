# Optimized strlen Function with SIMD

This program implements and benchmarks several versions of the strlen function to calculate the length of a null-terminated string. It includes the following versions:

- Standard strlen: Uses the standard C library strlen.
- 64-bit Chunk SIMD: Reads 8 bytes (64 bits) at a time to check for null bytes.
- SSE SIMD: Uses SSE instructions to check for null bytes 16 bytes at a time.
- AVX2 SIMD: Uses AVX2 instructions to check for null bytes 32 bytes at a time.

## How It Works

- **Standard strlen**: This uses the basic byte-by-byte comparison provided by the C standard library.
- **SIMD Optimizations**: Instead of checking one byte at a time, the program uses 64-bit chunks (8 bytes), SSE (16 bytes), or AVX2 (32 bytes) instructions to process multiple bytes in parallel. Once a chunk with a null byte is detected, it falls back to a byte-by-byte check to find the exact position of the null terminator.
- **Performance Measurement**: The execution time for each method is measured and compared.

## Compilation

To compile the program, use the following command:

```bash
gcc -o strlen_simd strlen_simd.c -mavx2 -msse4.2 -lm
```

This will produce an executable named strlen_simd.

To run the program, simply execute:

```bash
./strlen_simd
```
