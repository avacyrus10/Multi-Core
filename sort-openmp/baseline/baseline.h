#ifndef SORT_BASELINE_H
#define SORT_BASELINE_H

#include <stddef.h>
#include <stdint.h>
#include <omp.h>

#include "config.h"
#include "util.h"

double baseline_qsort(T *array, size_t size);

#endif //SORT_BASELINE_H
