cmake_minimum_required(VERSION 3.26)
project(sort C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-fopenmp -O3")


add_executable(static_bench_1 benches/static_sort_bench.c
        config.h
        utils/util.h
        static/static_qsort.c
        static/static_qsort.h
        utils/random_gen.c
        utils/random_gen.h
        baseline/baseline.c
        baseline/baseline.h
)


add_executable(static_bench_2 benches/static_sort_bench.c
        config.h
        utils/util.h
        static/static_qsort.c
        static/static_qsort.h
        utils/random_gen.c
        utils/random_gen.h
        baseline/baseline.c
        baseline/baseline.h
)

set_target_properties(static_bench_1 PROPERTIES COMPILE_FLAGS "-DBENCH1")
set_target_properties(static_bench_2 PROPERTIES COMPILE_FLAGS "-DBENCH2")


add_executable(dynamic_bench1 benches/dynamic_sort_bench.c
        config.h
        utils/util.h
        dynamic/dynamic_qsort.c
        dynamic/dynamic_qsort.h
        utils/random_gen.c
        utils/random_gen.h
        baseline/baseline.c
        baseline/baseline.h
)

add_executable(dynamic_bench2 benches/dynamic_sort_bench.c
        config.h
        utils/util.h
        dynamic/dynamic_qsort.c
        dynamic/dynamic_qsort.h
        utils/random_gen.c
        utils/random_gen.h
        baseline/baseline.c
        baseline/baseline.h
)

set_target_properties(dynamic_bench1 PROPERTIES COMPILE_FLAGS "-DBENCH1")
set_target_properties(dynamic_bench2 PROPERTIES COMPILE_FLAGS "-DBENCH2")

include_directories("." "./utils")

