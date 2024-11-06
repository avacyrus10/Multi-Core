#ifndef DENSE_H
#define DENSE_H

void dense_matvec_mult(int rows, int cols, float **matrix, float *vector, float *result);
float **generate_dense_matrix(int rows, int cols);
float *generate_vector(int size);

#endif

