cc = gcc
flags = -fopenmp -O3

files = $(wildcard *.c) $(wildcard */*.c)
# filter out cmake-build-debug dir
files := $(filter-out cmake-build-debug/%,$(files))
# filter out benches dir
files := $(filter-out benches/%,$(files))

# get all dirs in current dir
dirs = $(wildcard */)

# add -I to all dirs and remove last char (/)
dirs := $(addprefix -I,$(dirs))
dirs := $(subst /,,$(dirs))

.PHONY: all clean static_bench_1 static_bench_2 dynamic_bench_1 dynamic_bench_2 compare_all_bench

all: static_bench_1 static_bench_2 dynamic_bench_1 dynamic_bench_2 compare_all_bench

# Static and dynamic bench targets
static_bench_1: $(files)
	$(cc) $(flags) -o ./benches/static_bench_1 -I. $(dirs) $(files) ./benches/static_sort_bench.c -DBENCH1

static_bench_2: $(files)
	$(cc) $(flags) -o ./benches/static_bench_2 -I. $(dirs) $(files) ./benches/static_sort_bench.c -DBENCH2

dynamic_bench_1: $(files)
	$(cc) $(flags) -o ./benches/dynamic_bench_1 -I. $(dirs) $(files) ./benches/dynamic_sort_bench.c -DBENCH1

dynamic_bench_2: $(files)
	$(cc) $(flags) -o ./benches/dynamic_bench_2 -I. $(dirs) $(files) ./benches/dynamic_sort_bench.c -DBENCH2

# Benchmark for comparing all sorting versions
compare_all_bench: $(files)
	$(cc) $(flags) -o ./benches/compare_all_bench -I. $(dirs) $(files) ./benches/compare_all_bench.c
	./benches/compare_all_bench  # Automatically run it after compilation

clean:
	rm -rf ./benches/static_bench_1 ./benches/static_bench_2 ./benches/dynamic_bench_1 ./benches/dynamic_bench_2 ./benches/compare_all_bench
