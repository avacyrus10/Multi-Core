#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dense.h"
#include "sparse.h"

// load a dense matrix from a file
float **load_dense_matrix_from_file(const char *filename, int rows, int cols) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open matrix file.\n");
        return NULL;
    }

    float **matrix = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (float *)malloc(cols * sizeof(float));
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%f", &matrix[i][j]);  
        }
    }

    fclose(file);
    return matrix;
}

// load a vector from a file
float *load_vector_from_file(const char *filename, int size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open vector file.\n");
        return NULL;
    }

    float *vector = (float *)malloc(size * sizeof(float));
    for (int i = 0; i < size; i++) {
        fscanf(file, "%f", &vector[i]); 
    }

    fclose(file);
    return vector;
}

int main() {
    int rows = 1000, cols = 1000;

    // Load the matrix and vector from files
    float **matrix = load_dense_matrix_from_file("matrix.txt", rows, cols);
    float *vector = load_vector_from_file("vector.txt", cols);
    float *result = (float *)malloc(rows * sizeof(float));

    clock_t start, end;
    double time_taken;

    // Dense matrix-vector multiplication
    start = clock();
    dense_matvec_mult(rows, cols, matrix, vector, result);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Dense Matrix-Vector Multiplication Done. Time: %f seconds\n", time_taken);

    // Convert the dense matrix to CSR format
    CSRMatrix csr = dense_to_csr(matrix, rows, cols);

    // Sparse matrix-vector multiplication (Single-threaded)
    start = clock();
    csr_matvec_mult(&csr, vector, result, rows);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sparse Matrix-Vector Multiplication (Single-threaded) Done. Time: %f seconds\n", time_taken);

    // Sparse matrix-vector multiplication (Multi-threaded with OpenMP)
    start = clock();
    csr_matvec_mult_omp(&csr, vector, result, rows);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sparse Matrix-Vector Multiplication (Multi-threaded) Done. Time: %f seconds\n", time_taken);

    // sparse matrix-vector multiplication with SIMD (AVX)
    start = clock();
    csr_matvec_mult_avx(&csr, vector, result, rows);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sparse Matrix-Vector Multiplication (SIMD) Done. Time: %f seconds\n", time_taken);


    free(csr.row_ptr);
    free(csr.col_ind);
    free(csr.values);
    free(vector);
    free(result);

    return 0;
}

