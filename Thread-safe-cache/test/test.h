#ifndef CCACHE_TEST_H
#define CCACHE_TEST_H

#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>

#include "../src/cache.h"

typedef struct {
    cache_t *cache;
    pthread_barrier_t *barrier;
    sem_t *semaphore;
    const char *key;
    const void *generator_arg;
} worker_arg_t;

const char *example_generator(const char *key, const void *arg);

const char *error_generator(const char *key, const void *arg);

const char *counting_generator(const char *key, const void *arg);

void *test_no_duplicate_sequential(void *arg);

void *test_no_duplicate_concurrent(void *arg);

void *test_no_block_disjoint(void *arg);

void *test_no_block_reader(void *arg);

#endif /* CCACHE_TEST_H */