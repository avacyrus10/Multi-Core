#include <immintrin.h>
#include <stdio.h>
#include <time.h>


// Calculate reciprocal square root using Newton-Raphson iteration
void avx_q_rsqrt(float input[8], float output[8]) {
    __m256 x = _mm256_loadu_ps(input);
    __m256 half = _mm256_set1_ps(0.5f);
    __m256 three_halfs = _mm256_set1_ps(1.5f);


    __m256 y0 = _mm256_rsqrt_ps(x);
    __m256 x2 = _mm256_mul_ps(x, half);
    __m256 y1 = _mm256_mul_ps(three_halfs - _mm256_mul_ps(x2, _mm256_mul_ps(y0, y0)), y0);


    _mm256_storeu_ps(output, y1);
}

float q_rsqrt(float number) {
    long i;
    float x2, y;
    const float three_halfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (three_halfs - (x2 * y * y));

    return y;
}

int main() {
    float input[8] = {4.0f, 9.0f, 16.0f, 25.0f, 36.0f, 49.0f, 64.0f, 81.0f};
    float output_avx[8];
    float output_quake[8];


    clock_t start_avx = clock();
    avx_q_rsqrt(input, output_avx);
    clock_t end_avx = clock();
    double avx_duration = ((double)(end_avx - start_avx)) / CLOCKS_PER_SEC;


    clock_t start_quake = clock();
    for (int i = 0; i < 8; ++i) {
        output_quake[i] = q_rsqrt(input[i]);
    }
    clock_t end_quake = clock();
    double quake_duration = ((double)(end_quake - start_quake)) / CLOCKS_PER_SEC;

  
    printf("Input: ");
    for (int i = 0; i < 8; ++i) {
        printf("%.2f  ", input[i]);
    }
    printf("\n");

    printf("AVX Approximate 1/sqrt(x): ");
    for (int i = 0; i < 8; ++i) {
        printf("%.6f  ", output_avx[i]);
    }
    printf("\n");

    printf("Quake III Approximate 1/sqrt(x): ");
    for (int i = 0; i < 8; ++i) {
        printf("%.6f  ", output_quake[i]);
    }
    printf("\n");

    printf("AVX Execution Time: %.6f seconds\n", avx_duration);
    printf("Quake III Execution Time: %.6f seconds\n", quake_duration);

    return 0;
}
