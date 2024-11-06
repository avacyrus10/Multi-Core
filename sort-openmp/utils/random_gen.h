#ifndef SORT_RANDOM_GEN_H
#define SORT_RANDOM_GEN_H


#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "config.h"


void gen_random_array(T *array, size_t size);

void gen_semi_sorted_array(T *array, size_t size);

#endif //SORT_RANDOM_GEN_H
