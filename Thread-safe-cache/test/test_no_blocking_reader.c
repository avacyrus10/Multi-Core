#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../src/cache.h"
#include "test.h"

typedef struct {
    cache_t *cache;
    sem_t *first_worker_semaphore;
    sem_t *third_worker_semaphore;
} no_block_reader_first_generator_arg_t;

typedef struct {
    cache_t *cache;
    sem_t *first_worker_semaphore;
    sem_t *third_worker_semaphore;
    const char *key;
    const void *generator_arg;
} no_block_reader_first_worker_arg_t;

static pthread_t threads[3];

void *cache_no_block_reader_second_worker(void *arg) {
    worker_arg_t *worker_arg = (worker_arg_t *)arg;
    cache_t *cache = worker_arg->cache;
    const char *key = worker_arg->key;
    const void *generator_arg = worker_arg->generator_arg;
    assert(strcmp(cache_get_or_insert_with(cache, key, error_generator, generator_arg), key) == 0);

    return NULL;
}

void *cache_no_block_reader_third_worker(void *arg) {
    worker_arg_t *worker_arg = (worker_arg_t *)arg;
    cache_t *cache = worker_arg->cache;
    sem_t *semaphore = worker_arg->semaphore;
    const char *key = worker_arg->key;
    const void *generator_arg = worker_arg->generator_arg;
    assert(strcmp(cache_get_or_insert_with(cache, key, example_generator, generator_arg), key) == 0);
    sem_post(semaphore);

    return NULL;
}

const char *cache_no_block_reader_first_worker_generator(const char *key, const void *arg) {
    no_block_reader_first_generator_arg_t *generator_arg = (no_block_reader_first_generator_arg_t *)arg;
    cache_t *cache = generator_arg->cache;
    sem_t *first_semaphore = generator_arg->first_worker_semaphore;
    sem_t *third_semaphore = generator_arg->third_worker_semaphore;

    worker_arg_t second_worker_arg = {cache, NULL, NULL, "key1", NULL};
    worker_arg_t third_worker_arg = {cache, NULL, third_semaphore, "key3", NULL};
    pthread_create(&threads[1], NULL, cache_no_block_reader_second_worker, &second_worker_arg);
    pthread_create(&threads[1], NULL, cache_no_block_reader_third_worker, &third_worker_arg);

    sem_wait(first_semaphore);

    return key;
}

void *cache_no_block_reader_first_worker(void *arg) {
    no_block_reader_first_worker_arg_t *worker_arg = (no_block_reader_first_worker_arg_t *)arg;
    cache_t *cache = worker_arg->cache;
    const char *key = worker_arg->key;
    const void *generator_arg = worker_arg->generator_arg;
    assert(strcmp(cache_get_or_insert_with(cache, key, cache_no_block_reader_first_worker_generator, generator_arg), key) == 0);

    return NULL;
}

void *test_no_block_reader(void *arg) {
    cache_t cache;
    cache_init(&cache);

    sem_t first_worker_semaphore;
    sem_init(&first_worker_semaphore, 0, 0);
    sem_t third_worker_semaphore;
    sem_init(&third_worker_semaphore, 0, 0);
    no_block_reader_first_generator_arg_t first_generator_arg = {&cache, &first_worker_semaphore,
                                                                 &third_worker_semaphore};
    no_block_reader_first_worker_arg_t first_worker_arg = {&cache, &first_worker_semaphore, &third_worker_semaphore,
                                                           "key1", &first_generator_arg};
    pthread_create(&threads[0], NULL, cache_no_block_reader_first_worker, &first_worker_arg);

    sleep(2);
    struct timespec timeout = {3, 0};
    sem_timedwait(&third_worker_semaphore, &timeout);
    sem_post(&first_worker_semaphore);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

    cache_destroy(&cache);
    sem_destroy(&first_worker_semaphore);
    sem_destroy(&third_worker_semaphore);

    return NULL;
}