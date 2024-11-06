#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

#include "../src/cache.h"
#include "test.h"

void *test_no_duplicate_sequential(void *arg) {
    cache_t cache;
    cache_init(&cache);

    assert(strcmp(cache_get_or_insert_with(&cache, "key1", example_generator, "key1"), "key1") == 0);
    assert(strcmp(cache_get_or_insert_with(&cache, "key2", example_generator, "key2"), "key2") == 0);

    assert(strcmp(cache_get_or_insert_with(&cache, "key1", error_generator, "key1"), "key1") == 0);
    assert(strcmp(cache_get_or_insert_with(&cache, "key2", error_generator, "key2"), "key2") == 0);

    cache_destroy(&cache);

    return NULL;
}

void *no_duplicate_concurrent_worker(void *arg) {
    worker_arg_t *worker_arg = (worker_arg_t *)arg;
    cache_t *cache = worker_arg->cache;
    const char *key = worker_arg->key;
    const void *generator_arg = worker_arg->generator_arg;
    pthread_barrier_t *barrier = worker_arg->barrier;
    pthread_barrier_wait(barrier);
    assert(strcmp(cache_get_or_insert_with(cache, key, counting_generator, generator_arg), key) == 0);

    return NULL;
}

void *test_no_duplicate_concurrent(void *arg) {
    cache_t cache;
    cache_init(&cache);

    pthread_t threads[16];
    atomic_int counter = 0;

    pthread_barrier_t first_barrier;
    pthread_barrier_init(&first_barrier, NULL, 8);
    worker_arg_t first_worker_arg = {&cache, &first_barrier, NULL, "key1", &counter};
    pthread_barrier_t second_barrier;
    pthread_barrier_init(&second_barrier, NULL, 8);
    worker_arg_t second_worker_arg = {&cache, &second_barrier, NULL, "key2", &counter};

    for (int i = 0; i < 8; i++) {
        pthread_t *thread = &threads[i];
        pthread_create(thread, NULL, no_duplicate_concurrent_worker, &first_worker_arg);
    }
    for (int i = 8; i < 16; i++) {
        pthread_t *thread = &threads[i];
        pthread_create(thread, NULL, no_duplicate_concurrent_worker, &second_worker_arg);
    }

    for (int i = 0; i < 16; i++) {
        pthread_join(threads[i], NULL);
    }

    assert(counter == 2);

    pthread_barrier_destroy(&first_barrier);
    pthread_barrier_destroy(&second_barrier);
    cache_destroy(&cache);

    return NULL;
}
