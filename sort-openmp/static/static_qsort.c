#include "static_qsort.h"

void swap(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

T partition(T *array, size_t low, size_t high) {
    T pivot = array[high];
    size_t i = low;

    for (size_t j = low; j < high; j++) {
        if (array[j] <= pivot) {
            swap(&array[i], &array[j]);
            i++;
        }
    }
    swap(&array[i], &array[high]);
    return i;
}

void quicksort(T *array, size_t low, size_t high) {
    if (low < high) {
        T pivot = partition(array, low, high);

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                quicksort(array, low, pivot - 1);
            }
            #pragma omp section
            {
                quicksort(array, pivot + 1, high);
            }
        }
    }
}

double static_qsort(T *array, size_t size) {
    double start = omp_get_wtime();
    quicksort(array, 0, size - 1);
    return omp_get_wtime() - start;
}

/*
+---------------------------------------------------+
| Benchmark 1                                       |
+-------------------------+-------------------------+
| baseline_qsort          | static_qsort            |
+-------------------------+-------------------------+
| 0.7545081600            | 2.2656590120            |
+-------------------------+-------------------------+

As its shown in the results using parallel sections(which will schedule statically) the algorithm is running much slower. 
By default we don’t have nested parallel sections in openmmp(omp_set_nested(0)) due the large number of threads
needed which will cause a great overhead.

libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: 
libgomp: Thread creation failed: Resource temporarily unavailable

On the second bench we are enabling nested parallel sections by setting omp_set_nested(1) so for each recursive call another
parallel section is created and the number of threads will be more than our available resources, thus it cant be run.

We can conclude that using static scheduling is not a good choice for recursive functions due to its high overhead.

*/