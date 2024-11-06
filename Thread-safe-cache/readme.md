# Thread-Safe Key-Value Cache (C Implementation)

This project implements a thread-safe key-value cache in C using the pthread API. The cache allows concurrent access to different keys, ensuring that resource-intensive functions (f) associated with each key are only executed once per key, even in the presence of concurrent invocations.
## Features
- **Thread-Safe**: Implements fine-grained locking to allow concurrent access to different keys in the cache.
- **Non-Blocking for Different Keys**: If two threads request different keys, they proceed concurrently without blocking each other.
- **Work Deduplication**: If multiple threads request the same key, the function generator() is executed only once, avoiding redundant computations.

## How It Works

- **Cache API**:
  
    ```c
    cache_get_or_insert_with(cache_t *cache, const char *key, generator_t generator, const void *arg)
    ```
    - Retrieves the value associated with the `key` if it already exists in the cache.
    - If the `key` does not exist, the function `generator()` is invoked, the result is inserted into the cache, and the result is returned.
    - For concurrent requests with the same key, the function `generator()` is guaranteed to be executed only once.

- **Concurrency**:
    - The cache uses fine-grained locks (mutexes) to ensure thread safety, allowing concurrent access to different keys.
    - The `pthread` library is used to create and manage threads.


