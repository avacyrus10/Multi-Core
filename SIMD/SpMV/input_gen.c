#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// generate a random dense matrix and store it in a file
void generate_dense_matrix_to_file(const char *filename, int rows, int cols) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float val = (rand() % 10) + 1;
            fprintf(file, "%f ", val);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// generate a random vector and store it in a file
void generate_vector_to_file(const char *filename, int size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        float val = (rand() % 10) + 1;
        fprintf(file, "%f\n", val);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <rows> <cols> <vector_size>\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int vector_size = atoi(argv[3]);

    srand(time(NULL));

    // Generate the matrix and vector
    generate_dense_matrix_to_file("matrix.txt", rows, cols);
    generate_vector_to_file("vector.txt", vector_size);

    printf("Matrix and vector generated and stored in files.\n");

    return 0;
}

