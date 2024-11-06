#ifndef SPARSE_H
#define SPARSE_H

typedef struct {
    int *row_ptr;
    int *col_ind;
    float *values;
} CSRMatrix;

CSRMatrix dense_to_csr(float **matrix, int rows, int cols);
void csr_matvec_mult(CSRMatrix *csr, float *vector, float *result, int rows);
void csr_matvec_mult_omp(CSRMatrix *csr, float *vector, float *result, int rows);
void csr_matvec_mult_avx(CSRMatrix *csr, float *vector, float *result, int rows);

#endif

