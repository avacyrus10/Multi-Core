#include <omp.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "baseline/baseline.h"
#include "random_gen.h"
#include "static/static_qsort.h"    // Static sort implementation
#include "dynamic/dynamic_qsort.h"  // Dynamic sort implementation
#include "my_version/my_qsort.h"    // Your custom version

// Define the MIN macro
#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

// Helper function to print an array (for debugging)
void print_array(T *array, size_t size, const char *label) {
    printf("%s: [", label);
    for (size_t i = 0; i < MIN(size, 20); ++i) {  // Print only the first 20 elements for brevity
        printf("%ld ", (int64_t) array[i]);  // Adjust format to match int64_t
    }
    printf("...]\n");
}

// Benchmark function to compare baseline, static, dynamic, and custom quicksort
void bench_compare_all() {
    size_t size = 10000000;  // Test with a large array
    omp_set_num_threads(omp_get_max_threads());  // Set max threads

    // Generate a random array
    T *input_vector = (T *) malloc(sizeof(T) * size);
    gen_random_array(input_vector, size);

    // Make three copies of the original input vector for comparison
    T *input_vector2 = (T *) malloc(sizeof(T) * size);
    T *input_vector3 = (T *) malloc(sizeof(T) * size);
    T *input_vector4 = (T *) malloc(sizeof(T) * size);
    memcpy(input_vector2, input_vector, sizeof(T) * size);
    memcpy(input_vector3, input_vector, sizeof(T) * size);
    memcpy(input_vector4, input_vector, sizeof(T) * size);

    // Debug: Print the first few elements of the input arrays
    print_array(input_vector, size, "Original Array");
    
    // Sort with baseline (sequential quicksort)
    double time_baseline = baseline_qsort(input_vector, size);
    print_array(input_vector, size, "Baseline Sorted Array");

    // Sort with static scheduling parallel sort
    double time_static = static_qsort(input_vector2, size);
    print_array(input_vector2, size, "Static Sorted Array");

    // Sort with dynamic scheduling parallel sort
    double time_dynamic = dynamic_qsort(input_vector3, size);
    print_array(input_vector3, size, "Dynamic Sorted Array");

    // Sort with your custom version (my_qsort)
    double time_custom = my_qsort(input_vector4, size);
    print_array(input_vector4, size, "Custom Sorted Array");

    // Verify sorting
    ASSERT(IS_SORTED(input_vector, size));
    ASSERT(IS_SORTED(input_vector2, size));
    ASSERT(IS_SORTED(input_vector3, size));
    ASSERT(IS_SORTED(input_vector4, size));  // This is where the issue occurs

    // Print the benchmark results
    printf("+---------------------------------------------------+\n");
    printf("| Benchmark - Compare All Sorts                     |\n");
    printf("+-------------------------+-------------------------+\n");
    printf("| baseline_qsort          | %.10lf                  |\n", time_baseline);
    printf("| static_qsort            | %.10lf                  |\n", time_static);
    printf("| dynamic_qsort           | %.10lf                  |\n", time_dynamic);
    printf("| my_qsort (custom)       | %.10lf                  |\n", time_custom);
    printf("+-------------------------+-------------------------+\n");

    // Free allocated memory
    free(input_vector);
    free(input_vector2);
    free(input_vector3);
    free(input_vector4);
}

int main() {
    bench_compare_all();
    return 0;
}
