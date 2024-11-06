#ifndef SORT_STATIC_QSORT_H
#define SORT_STATIC_QSORT_H


#include <stdint.h>
#include <stdbool.h>
#include <omp.h>

#include "config.h"
#include "stddef.h"
#include "utils/util.h"

double static_qsort(T *array, size_t size);

#endif //SORT_STATIC_QSORT_H
