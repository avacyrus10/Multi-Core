#include "random_gen.h"
#include "util.h"


void gen_random_array(T *array, size_t size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % size;
    }
}


void gen_semi_sorted_array(T *array, size_t size) {
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }

    for (int i = 0; i < size / 2; i++) {
        int index1 = rand() % size;
        int index2 = rand() % size;

        SWAP(array[index1], array[index2]);
    }
}




