#ifndef DIPLOMA_LAPACK_CALC_LAPACK_CALC_H
#define DIPLOMA_LAPACK_CALC_LAPACK_CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f2c.h"
#include "clapack.h"
#include <math.h>

int matrix_columns, matrix_rows, constan_term_rows;

FILE *get_file(char *filename);

void save_result(complex *constan_terms, int length);

complex *get_matrix(FILE *file_real_matrix, FILE *file_image_matrix);

complex *get_constant_term(FILE *file_real_constant_term, FILE *file_image_constant_term);

#endif //DIPLOMA_LAPACK_CALC_LAPACK_CALC_H
