# Parallel Sorting Algorithms with OpenMP

This project implements various parallel sorting algorithms using OpenMP for efficient multi-threaded sorting. It includes a custom hybrid merge sort, as well as static and dynamic quicksort implementations. The hybrid merge sort adapts between parallel and sequential processing based on a threshold, while the static and dynamic versions utilize different scheduling strategies for parallelism. The project also includes benchmarking to compare the performance of these methods.

## Features

- **Hybrid Merge Sort**: Combines parallel and sequential sorting to reduce task overhead.
- **Static and Dynamic Quicksort**: Implements both static and dynamic scheduling strategies for parallel quicksort.
- **OpenMP Parallelism**: Uses OpenMP tasks and threads to leverage multi-core processing.
- **Customizable Threshold**: Allows tuning for hybrid sorting to optimize performance based on array size.
- **Performance Comparison**: Benchmarks different sorting methods to evaluate their speed and efficiency.

## Requirements

- **GCC**: Ensure GCC is installed with OpenMP support.
- **OpenMP**: Required for parallel processing.
- **Make** (optional): For building with the provided Makefile.

## Compilation

1. **Clone the Repository**:

   ```bash
   git clone <repository_url>
   cd sort-openmp
## Compile with Make:

To compile and run the project, use the following command:
```bash
make compare_all_bench
```


