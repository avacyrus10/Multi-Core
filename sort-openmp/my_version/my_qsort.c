#include "my_qsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define THRESHOLD 1000
#define MAX_THREADS 5
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


inline void merge(T *array, size_t low, size_t mid, size_t high, T *tempArray) {
    size_t left = low, right = mid + 1, index = low;

    while (left <= mid && right <= high) {
        tempArray[index++] = (array[left] <= array[right]) ? array[left++] : array[right++];
    }

    while (left <= mid) {
        tempArray[index++] = array[left++];
    }

    while (right <= high) {
        tempArray[index++] = array[right++];
    }

    for (index = low; index <= high; ++index) {
        array[index] = tempArray[index];
    }
}

void sequential_merge_sort(T *array, size_t low, size_t high, T *tempArray) {
    if (low < high) {
        size_t mid = low + (high - low) / 2;
        sequential_merge_sort(array, low, mid, tempArray);
        sequential_merge_sort(array, mid + 1, high, tempArray);
        merge(array, low, mid, high, tempArray);
    }
}

void hybrid_merge_sort(T *array, size_t low, size_t high, T *tempArray) {
    if (low < high) {
        if (high - low + 1 <= THRESHOLD) {
            sequential_merge_sort(array, low, high, tempArray);
        } else {
            size_t mid = low + (high - low) / 2;

            #pragma omp task shared(array, tempArray) if(high - low > THRESHOLD)
            hybrid_merge_sort(array, low, mid, tempArray);

            #pragma omp task shared(array, tempArray) if(high - low > THRESHOLD)
            hybrid_merge_sort(array, mid + 1, high, tempArray);

            #pragma omp taskwait
            merge(array, low, mid, high, tempArray);
        }
    }
}

double my_qsort(T *array, size_t size) {
    T *tempArray = (T *)malloc(size * sizeof(T));
    if (!tempArray) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    double start = omp_get_wtime();
    omp_set_num_threads(MAX_THREADS);

    #pragma omp parallel
    {
        #pragma omp single
        hybrid_merge_sort(array, 0, size - 1, tempArray);
    }

    double execution_time = omp_get_wtime() - start;

    free(tempArray);
    return execution_time;
}
