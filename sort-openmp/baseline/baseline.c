#include "baseline.h"


static void quicksort_rec_seq(T *array, size_t start, size_t end);

/**
 * @brief Sorts an array using the QuickSort algorithm.
 *
 * This function sorts the elements of the given array in ascending order using
 * the QuickSort algorithm. The sort is performed in-place, meaning that the
 * original array will be modified.
 *
 * @param array The array to be sorted.
 * @param size The number of elements in the array.
 */
double baseline_qsort(T *array, size_t size) {
    double start = omp_get_wtime();
    quicksort_rec_seq(array, 0, size - 1);
    return omp_get_wtime() - start;
}


/**
 * \brief Performs sequential quicksort recursively on an array.
 *
 * This function performs sequential quicksort recursively on an array in the specified range.
 * It uses the specified partition method to partition the array and recursively sorts the sub-arrays
 * before and after the pivot.
 *
 * \param array Pointer to the array that will be sorted.
 * \param start The starting index of the range to be sorted.
 * \param end The ending index of the range to be sorted.
 */
static void quicksort_rec_seq(T *array, size_t start, size_t end) { // NOLINT(*-no-recursion)
    if (start >= end) return;

    size_t pivot = PARTITION(array, start, end);

    quicksort_rec_seq(array, start, pivot - 1);
    quicksort_rec_seq(array, pivot, end);
}