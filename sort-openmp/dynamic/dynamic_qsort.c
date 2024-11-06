#include "dynamic_qsort.h"


void swapd(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

T partitiond(T *array, size_t low, size_t high) {
    T pivot = array[high];
    size_t i = low;

    for (size_t j = low; j < high; j++) {
        if (array[j] <= pivot) {
            swapd(&array[i], &array[j]);
            i++;
        }
    }
    swapd(&array[i], &array[high]);
    return i;
}

void dynamic_quicksort(T *array, size_t low, size_t high) {
    if (low < high) {
        T pivot = partitiond(array, low, high);


            #pragma omp task
            {
                dynamic_quicksort(array, low, pivot - 1);
            }
            #pragma omp task
            {
                dynamic_quicksort(array, pivot + 1, high);
            }
        
    }
}

double dynamic_qsort(T *array, size_t size) {
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            dynamic_quicksort(array, 0, size - 1);
        }
    }

    return omp_get_wtime() - start;
}
/*
+---------------------------------------------------+
| Benchmark 2                                       |
+-------------------------+-------------------------+
| baseline_qsort          | dynamic_qsort            |
+-------------------------+-------------------------+
| 0.0002187800            | 0.0034299470            |
+-------------------------+-------------------------+

+---------------------------------------------------+
| Benchmark 1                                       |
+-------------------------+-------------------------+
| baseline_qsort          | dynamic_qsort            |
+-------------------------+-------------------------+
| 0.7559389670            | 0.2400695940            |
+-------------------------+-------------------------+
 For the first benchmark we are using larger data thus the execution time of both implementation is much
 higher than the second benchmark.
 As we are using dynamic scheduling for this part we can get a much better performance in comparesion to
 the static scheduling, however it's still not better than baseline implementation for smaller inputs as 
 the overhead of parallelism outweights it's speedup, but as the size of our inputs getting larger the 
 dynamic quick sort can beat the baseline implementation.


*/