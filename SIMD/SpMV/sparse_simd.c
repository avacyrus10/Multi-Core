#include <immintrin.h>
#include "sparse.h"

void csr_matvec_mult_avx(CSRMatrix *csr, float *vector, float *result, int rows) {
    for (int i = 0; i < rows; i++) {
        __m256 sum = _mm256_setzero_ps();
        for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j += 8) {
            __m256 val = _mm256_loadu_ps(&csr->values[j]);
            __m256 vec_val = _mm256_set_ps(
                vector[csr->col_ind[j + 7]], vector[csr->col_ind[j + 6]], 
                vector[csr->col_ind[j + 5]], vector[csr->col_ind[j + 4]], 
                vector[csr->col_ind[j + 3]], vector[csr->col_ind[j + 2]], 
                vector[csr->col_ind[j + 1]], vector[csr->col_ind[j]]);

            sum = _mm256_add_ps(sum, _mm256_mul_ps(val, vec_val));
        }
        float temp[8];
        _mm256_storeu_ps(temp, sum);
        result[i] = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7];
    }
}

