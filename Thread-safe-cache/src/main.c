#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cache.h"

#define clear_line() printf("\33[2K\r")

typedef struct {
    int id;
    char *key;
} job_t;

static cache_t cache;
static int job_count = 0;

void print_prompt() { printf("\n$%d> ", job_count); }

const char *generator(const char *key, const void *arg) {
    sleep(3);
    return key;
}

void *handle_input(void *arg) {
    job_t *job = (job_t *)arg;
    int id = job->id;
    char *key = job->key;
    const char *value = cache_get_or_insert_with(&cache, key, generator, NULL);
    clear_line();
    printf("%d: %s", id, value);
    print_prompt();

    return NULL;
}

int main() {
    setbuf(stdout, NULL);
    cache_init(&cache);
    printf("welcome!");
    while (true) {
        char *key = (char *)malloc(CACHE_MAX_KEY_LEN * sizeof(char));
        job_count++;
        print_prompt();
        if (fgets(key, CACHE_MAX_KEY_LEN, stdin) == NULL)
            break;
        job_t job = {.id = job_count, .key = key};
        pthread_t thread;
        pthread_create(&thread, NULL, handle_input, &job);
    }

    return 0;
}