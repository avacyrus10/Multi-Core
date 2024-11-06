#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <unistd.h>

#include "../src/cache.h"
#include "test.h"

int main() {
    pthread_t threads[4];
    pthread_create(&threads[0], NULL, test_no_duplicate_sequential, NULL);
    pthread_create(&threads[1], NULL, test_no_duplicate_concurrent, NULL);
    pthread_create(&threads[2], NULL, test_no_block_disjoint, NULL);
    pthread_create(&threads[3], NULL, test_no_block_reader, NULL);

    for (int i = 0; i < 4; i++)
        pthread_join(threads[i], NULL);

    printf("All tests passed!\n");

    return 0;
}
