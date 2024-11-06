#include <stdlib.h>
#include <stdio.h>
#include "sparse.h"

CSRMatrix dense_to_csr(float **matrix, int rows, int cols) {
    CSRMatrix csr;
    int nnz = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                nnz++;
            }
        }
    }

    csr.row_ptr = (int *)malloc((rows + 1) * sizeof(int));
    csr.col_ind = (int *)malloc(nnz * sizeof(int));
    csr.values = (float *)malloc(nnz * sizeof(float));

    int k = 0;
    csr.row_ptr[0] = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                csr.values[k] = matrix[i][j];
                csr.col_ind[k] = j;
                k++;
            }
        }
        csr.row_ptr[i + 1] = k;
    }

    return csr;
}

void csr_matvec_mult(CSRMatrix *csr, float *vector, float *result, int rows) {
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
            result[i] += csr->values[j] * vector[csr->col_ind[j]];
        }
    }
}

