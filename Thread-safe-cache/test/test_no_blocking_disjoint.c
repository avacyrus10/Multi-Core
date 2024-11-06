#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../src/cache.h"
#include "test.h"

const char *cache_no_block_disjoint_first_worker_generator(const char *key, const void *arg) {
    sem_t *semaphore = (sem_t *)arg;
    sleep(2);
    sem_wait(semaphore);
    return key;
}

void *cache_no_block_disjoint_first_worker(void *arg) {
    worker_arg_t *worker_arg = (worker_arg_t *)arg;
    cache_t *cache = worker_arg->cache;
    const char *key = worker_arg->key;
    const void *generator_arg = worker_arg->generator_arg;
    assert(strcmp(cache_get_or_insert_with(cache, key, cache_no_block_disjoint_first_worker_generator, generator_arg), key) == 0);

    return NULL;
}

void *cache_no_block_disjoint_second_worker(void *arg) {
    worker_arg_t *worker_arg = (worker_arg_t *)arg;
    cache_t *cache = worker_arg->cache;
    sem_t *semaphore = worker_arg->semaphore;
    const char *key = worker_arg->key;
    const void *generator_arg = worker_arg->generator_arg;
    sem_post(semaphore);
    assert(strcmp(cache_get_or_insert_with(cache, key, example_generator, generator_arg), key) == 0);

    return NULL;
}

void *test_no_block_disjoint(void *arg) {
    cache_t cache;
    cache_init(&cache);

    sem_t first_semaphore;
    sem_init(&first_semaphore, 0, 0);
    worker_arg_t first_worker_arg = {&cache, NULL, NULL, "key1", &first_semaphore};
    sem_t second_semaphore;
    sem_init(&second_semaphore, 0, 0);
    worker_arg_t second_worker_arg = {&cache, NULL, &second_semaphore, "key2", NULL};

    pthread_t threads[2];
    pthread_create(&threads[0], NULL, cache_no_block_disjoint_first_worker, &first_worker_arg);
    pthread_create(&threads[1], NULL, cache_no_block_disjoint_second_worker, &second_worker_arg);

    sleep(2);
    struct timespec timeout = {3, 0};
    sem_timedwait(&second_semaphore, &timeout);
    sem_post(&first_semaphore);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    cache_destroy(&cache);
    sem_destroy(&first_semaphore);
    sem_destroy(&second_semaphore);

    return NULL;
}
