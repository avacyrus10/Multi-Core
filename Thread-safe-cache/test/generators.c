#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "test.h"

const char *example_generator(const char *key, const void *arg) {
    // Example computation function
    // This is a simple identity function for demonstration purposes
    sleep(2);
    return key;
}

const char *error_generator(const char *key, const void *arg) {
    perror("You are generating a duplicate value");
    exit(1);
}

const char *counting_generator(const char *key, const void *arg) {
    sleep(2);

    atomic_int *counter = (atomic_int *)arg;
    *counter += 1;

    return key;
}