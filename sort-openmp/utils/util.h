#ifndef SORT_UTIL_H
#define SORT_UTIL_H

#define NOT_IMPLEMENTED return 0

#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", #condition, __FILE__, __LINE__); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)


#define PRINT_ARR(arr, size) \
    do{                      \
        for (size_t i = 0; i < size; i++) { \
            printf("%lu ", arr[i]); \
        } \
        printf("\n"); \
    } while(0)

#define SWAP(a, b) \
    do{            \
        typeof(a) tmp = a; \
        a = b; \
        b = tmp; \
    } while(0)


#define IS_SORTED(array, size) \
    ({ \
        bool sorted = true; \
        for (size_t i = 0; i < size - 1; i++) { \
            if (array[i] > array[i + 1]) { \
                sorted = false; \
                break; \
            } \
        } \
        sorted; \
    })


#define PARTITION(array, start, end) ({ \
    size_t _k_partition, _j_partition; \
    size_t _start_partition = (start); \
    size_t _end_partition = (end); \
    T _pivot_partition = array[(_start_partition + _end_partition) >> 1]; \
    SWAP(array[_end_partition], array[(_start_partition + _end_partition) >> 1]); \
    _k_partition = _start_partition; \
    _j_partition = _end_partition; \
    do { \
        while (array[_k_partition] < _pivot_partition) \
            _k_partition++; \
        while (array[_j_partition] > _pivot_partition) \
            _j_partition--; \
        if (_k_partition >= _j_partition) \
            break; \
        SWAP(array[_k_partition], array[_j_partition]); \
        _k_partition++; \
        _j_partition--; \
    } while (1); \
    _k_partition; \
})

#endif //SORT_UTIL_H
