#include <omp.h>
#include "sparse.h"

void csr_matvec_mult_omp(CSRMatrix *csr, float *vector, float *result, int rows) {
    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
            result[i] += csr->values[j] * vector[csr->col_ind[j]];
        }
    }
}

