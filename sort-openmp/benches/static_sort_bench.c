#include <omp.h>
#include <string.h>

#include "baseline/baseline.h"
#include "static/static_qsort.h"
#include "random_gen.h"
#include "stdio.h"


void static_bench_1() {
    size_t size = 10000000;
    omp_set_nested(0);
    omp_set_num_threads(omp_get_max_threads());

    // generate random array
    T *input_vector = (T *) malloc(sizeof(T) * size);
    gen_random_array(input_vector, size);

    // copy array
    T *input_vector2 = (T *) malloc(sizeof(T) * size);
    memcpy(input_vector2, input_vector, sizeof(T) * size);

    // sort with baseline
    double time = baseline_qsort(input_vector, size);

    // sort with static parallel mode
    double time2 = static_qsort(input_vector2, size);

    // check if sorted
   ASSERT(IS_SORTED(input_vector, size));
   ASSERT(IS_SORTED(input_vector2, size));

    // print result
    printf("+---------------------------------------------------+\n");
    printf("| Benchmark 1                                       |\n");
    printf("+-------------------------+-------------------------+\n");
    printf("| baseline_qsort          | static_qsort            |\n");
    printf("+-------------------------+-------------------------+\n");
    printf("| %.10lf            | %.10lf            |\n", time, time2);
    printf("+-------------------------+-------------------------+\n");

    free(input_vector);
    free(input_vector2);
}


void static_bench_2() {
    size_t size = 100000;
    omp_set_nested(1); // enable nested parallelism
    omp_set_num_threads(omp_get_max_threads());

    // generate random array
    T *input_vector = (T *) malloc(sizeof(T) * size);
    gen_random_array(input_vector, size);

    // copy array
    T *input_vector2 = (T *) malloc(sizeof(T) * size);
    memcpy(input_vector2, input_vector, sizeof(T) * size);

    // sort with baseline
    double time = baseline_qsort(input_vector, size);

    // sort with static parallel mode
    double time2 = static_qsort(input_vector2, size);

    // check if sorted
    ASSERT(IS_SORTED(input_vector, size));
    ASSERT(IS_SORTED(input_vector2, size));

    // print result
    printf("+---------------------------------------------------+\n");
    printf("| Benchmark 2                                       |\n");
    printf("+-------------------------+-------------------------+\n");
    printf("| baseline_qsort          | static_qsort            |\n");
    printf("+-------------------------+-------------------------+\n");
    printf("| %.10lf            | %.10lf            |\n", time, time2);
    printf("+-------------------------+-------------------------+\n");

}


int main() {

#ifdef BENCH1
    static_bench_1();
#endif

#ifdef BENCH2
    static_bench_2();
#endif

}