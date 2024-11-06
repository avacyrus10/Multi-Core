CC = gcc
CFLAGS = -O3 -Wall
LDFLAGS = -lm


SOURCES_DENSE = dense.c main.c sparse.c sparse_omp.c sparse_simd.c
SOURCES_INPUT_GEN = input_gen.c


all: run

run: $(SOURCES_DENSE)
	$(CC) $(CFLAGS) -mavx -o run $(SOURCES_DENSE) $(LDFLAGS)
	./run

dense: $(SOURCES_DENSE)
	$(CC) $(CFLAGS) -mavx -o dense $(SOURCES_DENSE) $(LDFLAGS)
	./dense

sparse: $(SOURCES_DENSE)
	$(CC) $(CFLAGS) -mavx -o sparse $(SOURCES_DENSE) $(LDFLAGS)
	./sparse

omp: $(SOURCES_DENSE)
	$(CC) $(CFLAGS) -fopenmp -o omp $(SOURCES_DENSE) $(LDFLAGS)
	./omp

simd: $(SOURCES_DENSE)
	$(CC) $(CFLAGS) -mavx2 -o simd $(SOURCES_DENSE) $(LDFLAGS)
	./simd

generate_input: $(SOURCES_INPUT_GEN)
	$(CC) $(CFLAGS) -o generate_input $(SOURCES_INPUT_GEN)
	./generate_input 1000 1000 1000  

clean:
	rm -f *.o run dense sparse omp simd generate_input

