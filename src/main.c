#include "include/lapack_calc.h"

extern int matrix_columns, matrix_rows, constan_term_rows;

int main() {

    FILE *file_real_matrix = get_file("real_part_matrix");
    FILE *file_image_matrix = get_file("imag_part_matrix");

    FILE *file_real_constant_term = get_file("real_part_constant_term");
    FILE *file_image_constant_term = get_file("image_part_constant_term");

    complex **matrix = get_matrix(file_real_matrix, file_image_matrix);
    complex **constan_terms = get_constant_term(file_real_constant_term, file_image_constant_term);

//    int cgetrf_(integer *m, integer *n, complex *a, integer *lda, integer *ipiv, integer *info);
//    cgetrf_(&N, &N, matrix[0], &N, &N, &N);
    return 0;
}