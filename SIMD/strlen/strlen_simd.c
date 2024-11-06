#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <immintrin.h>
#include <time.h>

size_t strlen_standard(const char* str) {
    return strlen(str);
}

int has_zero(uint64_t v) {
    return (((v) - 0x0101010101010101ULL) & (~v) & 0x8080808080808080ULL) != 0;
}

size_t strlen_simd(const char* str) {
    const uint64_t* str_ull = (const uint64_t*)str;
    size_t i;

    for (i = 0; ; i++) {
        uint64_t chunk = str_ull[i];
        if (has_zero(chunk)) {
            const char* byte_ptr = (const char*)&chunk;
            for (size_t j = 0; j < sizeof(uint64_t); j++) {
                if (byte_ptr[j] == '\0') {
                    return i * sizeof(uint64_t) + j;
                }
            }
        }
    }

    return i * sizeof(uint64_t); 
}

int has_zero_sse(const __m128i* v) {
    __m128i zero_mask = _mm_set1_epi8(0);
    __m128i cmp_result = _mm_cmpeq_epi8(*v, zero_mask);
    return _mm_movemask_epi8(cmp_result) != 0;
}

size_t strlen_simd_sse(const char* str) {
    const __m128i* str_sse = (const __m128i*)str;
    size_t i;

    for (i = 0; ; i++) {
        __m128i chunk = _mm_loadu_si128(&str_sse[i]);

        if (has_zero_sse(&chunk)) {
            const char* byte_ptr = (const char*)&chunk;
            for (size_t j = 0; j < sizeof(__m128i); j++) {
                if (byte_ptr[j] == '\0') {
                    return i * sizeof(__m128i) + j;
                }
            }
        }
    }

    return i * sizeof(__m128i);
}

int has_zero_avx2(const __m256i* v) {
    __m256i zero_mask = _mm256_set1_epi8(0);
    __m256i cmp_result = _mm256_cmpeq_epi8(*v, zero_mask);
    return _mm256_movemask_epi8(cmp_result) != 0;
}

size_t strlen_simd_avx2(const char* str) {
    const __m256i* str_avx2 = (const __m256i*)str;
    size_t i;

    for (i = 0; ; i++) {
        __m256i chunk = _mm256_loadu_si256(&str_avx2[i]);

        if (has_zero_avx2(&chunk)) {
            const char* byte_ptr = (const char*)&chunk;
            for (size_t j = 0; j < sizeof(__m256i); j++) {
                if (byte_ptr[j] == '\0') {
                    return i * sizeof(__m256i) + j;
                }
            }
        }
    }

    return i * sizeof(__m256i);
}

int main() {
    const char* test_string = "Hello, this is a test string!";

    // Measure standard strlen
    clock_t start_standard = clock();
    size_t len_standard = strlen_standard(test_string);
    clock_t end_standard = clock();
    printf("Standard strlen: %zu Time: %f seconds\n", len_standard, ((double)(end_standard - start_standard)) / CLOCKS_PER_SEC);

    // Measure SIMD (64-bit chunk) strlen
    clock_t start_simd = clock();
    size_t len_simd = strlen_simd(test_string);
    clock_t end_simd = clock();
    printf("SIMD strlen (64-bit chunk): %zu Time: %f seconds\n", len_simd, ((double)(end_simd - start_simd)) / CLOCKS_PER_SEC);

    // Measure SIMD (SSE) strlen
    clock_t start_simd_sse = clock();
    size_t len_simd_sse = strlen_simd_sse(test_string);
    clock_t end_simd_sse = clock();
    printf("SIMD strlen (SSE): %zu Time: %f seconds\n", len_simd_sse, ((double)(end_simd_sse - start_simd_sse)) / CLOCKS_PER_SEC);

    // Measure SIMD (AVX2) strlen
    clock_t start_simd_avx2 = clock();
    size_t len_simd_avx2 = strlen_simd_avx2(test_string);
    clock_t end_simd_avx2 = clock();
    printf("SIMD strlen (AVX2): %zu Time: %f seconds\n", len_simd_avx2, ((double)(end_simd_avx2 - start_simd_avx2)) / CLOCKS_PER_SEC);

    return 0;
}
