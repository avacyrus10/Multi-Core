#ifndef CCACHE_CACHE_H
#define CCACHE_CACHE_H

#include <pthread.h>
#include <stdbool.h>
#include <uthash.h>

#define CACHE_MAX_KEY_LEN 64
#define CACHE_MAX_VALUE_LEN CACHE_MAX_KEY_LEN

typedef const char *(*generator_t)(const char *, const void *);

// Define the cache entry type
typedef struct {
    // Your code here.
    char key[CACHE_MAX_KEY_LEN];
    char value[CACHE_MAX_VALUE_LEN];
    bool computing;
    UT_hash_handle hh; // Required for uthash
} cache_entry_t;

// Define the cache structure
typedef struct {
    cache_entry_t *data;
    pthread_mutex_t lock; // Add this line to include a mutex lock in cache_t
} cache_t;

void cache_init(cache_t *cache);

void cache_destroy(cache_t *cache);

const char *cache_get_or_insert_with(cache_t *cache, const char *key, generator_t f, const void *arg);

#endif /* CCACHE_CACHE_H */
