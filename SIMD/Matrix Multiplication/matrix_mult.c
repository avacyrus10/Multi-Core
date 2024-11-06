#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void generate_random_matrix(float matrix[16][16]);
void matrix_mult(float a[16][16], float b[16][16], float c[16][16]);
void matrix_mult_non_simd(float a[16][16], float b[16][16], float c[16][16]);
int compare_matrices(float a[16][16], float b[16][16], float tolerance);


double measure_execution_time(void (*function)(float[16][16], float[16][16], float[16][16]), float a[16][16], float b[16][16], float c[16][16]);

void generate_random_matrix(float matrix[16][16]) {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            matrix[i][j] = (float)rand() / RAND_MAX;
        }
    }
}
// SIMD  matrix multiplication optimized by loop unrolling.
void matrix_mult(float a[16][16], float b[16][16], float c[16][16]) {
for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
        __m256 sum1 = _mm256_setzero_ps();
        __m256 sum2 = _mm256_setzero_ps();
        __m256 sum3 = _mm256_setzero_ps();
        __m256 sum4 = _mm256_setzero_ps();

        for (int k = 0; k < 16; k += 4) {
            __m256 a_part1 = _mm256_loadu_ps(&a[i][k]);
            __m256 b_part1 = _mm256_loadu_ps(&b[k][j]);
            sum1 = _mm256_add_ps(sum1, _mm256_mul_ps(a_part1, b_part1));

            __m256 a_part2 = _mm256_loadu_ps(&a[i][k+1]);
            __m256 b_part2 = _mm256_loadu_ps(&b[k+1][j]);
            sum2 = _mm256_add_ps(sum2, _mm256_mul_ps(a_part2, b_part2));

            __m256 a_part3 = _mm256_loadu_ps(&a[i][k+2]);
            __m256 b_part3 = _mm256_loadu_ps(&b[k+2][j]);
            sum3 = _mm256_add_ps(sum3, _mm256_mul_ps(a_part3, b_part3));

            __m256 a_part4 = _mm256_loadu_ps(&a[i][k+3]);
            __m256 b_part4 = _mm256_loadu_ps(&b[k+3][j]);
            sum4 = _mm256_add_ps(sum4, _mm256_mul_ps(a_part4, b_part4));
        }


        sum1 = _mm256_add_ps(sum1, sum2);
        sum3 = _mm256_add_ps(sum3, sum4);
        sum1 = _mm256_add_ps(sum1, sum3);

        _mm256_storeu_ps(&c[i][j], sum1);
    }
}
}

void matrix_mult_non_simd(float a[16][16], float b[16][16], float c[16][16]) {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            c[i][j] = 0.0f;

            for (int k = 0; k < 16; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int compare_matrices(float a[16][16], float b[16][16], float tolerance) {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (fabs(a[i][j] - b[i][j]) > tolerance) {
                printf("Difference at position (%d, %d): %.9f vs %.9f\n", i, j, a[i][j], b[i][j]);
                return 0;
            }
        }
    }
    return 1;
}

double measure_execution_time(void (*function)(float[16][16], float[16][16], float[16][16]), float a[16][16], float b[16][16], float c[16][16]) {
    clock_t start_time = clock();
    function(a, b, c);
    clock_t end_time = clock();

    return ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
}

int main() {
    float a[16][16];
    float b[16][16];
    float c_simd[16][16];
    float c_non_simd[16][16];

    srand((unsigned int) time(NULL));


    generate_random_matrix(a);
    generate_random_matrix(b);


    double simd_execution_time = measure_execution_time(matrix_mult, a, b, c_simd);
    printf("SIMD Execution Time: %.6f seconds\n", simd_execution_time);


    double non_simd_execution_time = measure_execution_time(matrix_mult_non_simd, a, b, c_non_simd);
    printf("Non-SIMD Execution Time: %.6f seconds\n", non_simd_execution_time);

  
    if (compare_matrices(c_simd, c_non_simd, 1e-6)) {
        printf("\nResults are equal.\n");
    } else {
        printf("\nResults are not equal.\n");
    }

    return 0;
}
