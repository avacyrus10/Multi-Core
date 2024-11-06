#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <uthash.h>

#include "cache.h"

// Initialize the cache
void cache_init(cache_t *cache) {
    cache->data = NULL; // Initialize the hashmap
    pthread_mutex_init(&(cache->lock), NULL); // Initialize the cache lock
}

// Destroy the cache
void cache_destroy(cache_t *cache) {
    pthread_mutex_destroy(&(cache->lock)); //destroy the cache lock

    cache_entry_t *entry, *tmp;
    HASH_ITER(hh, cache->data, entry, tmp) {
        HASH_DEL(cache->data, entry);
        free(entry);
    }
}

const char *cache_get_or_insert_with(cache_t *cache, const char *key, generator_t generator, const void *arg) {
    cache_entry_t *entry = NULL;
    const char *value = NULL;

    pthread_mutex_lock(&(cache->lock)); 

    HASH_FIND_STR(cache->data, key, entry);
    if (entry != NULL) {
        value = entry->value;
        pthread_mutex_unlock(&(cache->lock)); // releease the cache lock
        return value;
    }

  
    //create a new cache entry
    cache_entry_t *new_entry = (cache_entry_t *)malloc(sizeof(cache_entry_t));
    if (new_entry == NULL) {
        //memory allocation failure
        pthread_mutex_unlock(&(cache->lock)); //release the cache lock
        return NULL;
    }

    strncpy(new_entry->key, key, sizeof(new_entry->key) - 1);
    new_entry->key[sizeof(new_entry->key) - 1] = '\0'; 


    const char *computed_value = generator(key, arg);

    strncpy(new_entry->value, computed_value, sizeof(new_entry->value) - 1);
    new_entry->value[sizeof(new_entry->value) - 1] = '\0'; 
    new_entry->computing = false;

    //insert the new entry into the cache
    HASH_ADD_STR(cache->data, key, new_entry);

    pthread_mutex_unlock(&(cache->lock)); 

    return new_entry->value;
}