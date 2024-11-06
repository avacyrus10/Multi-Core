#include <omp.h>
#include <string.h>

#include "baseline/baseline.h"
#include "random_gen.h"
#include "stdio.h"
#include "dynamic/dynamic_qsort.h"


void dynamic_bench1() {
    size_t size = 1000;
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
    double time2 = dynamic_qsort(input_vector2, size);

    // check if sorted
    ASSERT(IS_SORTED(input_vector, size));
    ASSERT(IS_SORTED(input_vector2, size));

    // print result
    printf("+---------------------------------------------------+\n");
    printf("| Benchmark 2                                       |\n");
    printf("+-------------------------+-------------------------+\n");
    printf("| baseline_qsort          | dynamic_qsort            |\n");
    printf("+-------------------------+-------------------------+\n");
    printf("| %.10lf            | %.10lf            |\n", time, time2);
    printf("+-------------------------+-------------------------+\n");

}

void dynamic_bench2() {
    size_t size = 10000000;
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
    double time2 = dynamic_qsort(input_vector2, size);

    // check if sorted
    ASSERT(IS_SORTED(input_vector, size));
    ASSERT(IS_SORTED(input_vector2, size));

    // print result
    printf("+---------------------------------------------------+\n");
    printf("| Benchmark 1                                       |\n");
    printf("+-------------------------+-------------------------+\n");
    printf("| baseline_qsort          | dynamic_qsort            |\n");
    printf("+-------------------------+-------------------------+\n");
    printf("| %.10lf            | %.10lf            |\n", time, time2);
    printf("+-------------------------+-------------------------+\n");

    free(input_vector);
    free(input_vector2);
}


int main() {

#ifdef BENCH1
    dynamic_bench1();
#endif
#ifdef BENCH2
    dynamic_bench2();
#endif
}