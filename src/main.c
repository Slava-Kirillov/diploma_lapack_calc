#include "include/lapack_calc.h"

extern int matrix_columns, matrix_rows, constan_term_rows;

int main() {

    FILE *file_real_matrix = get_file("real_part_matrix");
    FILE *file_image_matrix = get_file("imag_part_matrix");

    FILE *file_real_constant_term = get_file("real_part_constant_term");
    FILE *file_image_constant_term = get_file("image_part_constant_term");

    complex **matrix = get_matrix(file_real_matrix, file_image_matrix);
    complex **constan_terms = get_constant_term(file_real_constant_term, file_image_constant_term);

//TODO: тестовый код для расчета СЛАУ
//######################################################################################################################
    integer M = matrix_rows;
    integer N = matrix_columns;
    integer NRBS = 1;

    integer LDA = matrix_columns;
    integer LDB = constan_term_rows;
    integer INFO;

    integer ipiv[constan_term_rows];

    cgetrf_(&M, &N, *matrix, &LDA, ipiv, &INFO);
    cgetrs_("T", &N, &NRBS, *matrix, &LDA, ipiv, *constan_terms, &LDB, &INFO);

    printf("\n INFO=%d\n", (int) INFO);
//######################################################################################################################

    return 0;
}