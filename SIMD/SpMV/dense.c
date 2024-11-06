#include <stdlib.h>
#include <stdio.h>
#include "dense.h"

void dense_matvec_mult(int rows, int cols, float **matrix, float *vector, float *result) {
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

float **generate_dense_matrix(int rows, int cols) {
    float **matrix = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (float *)malloc(cols * sizeof(float));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (rand() % 10) + 1;
        }
    }
    return matrix;
}

float *generate_vector(int size) {
    float *vector = (float *)malloc(size * sizeof(float));
    for (int i = 0; i < size; i++) {
        vector[i] = (rand() % 10) + 1;
    }
    return vector;
}

