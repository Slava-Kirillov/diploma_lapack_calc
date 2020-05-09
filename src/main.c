#include "include/lapack_calc.h"
#include <time.h>

int main() {

    FILE *file_real_matrix = get_file("real_part_matrix");
    FILE *file_image_matrix = get_file("imag_part_matrix");

    FILE *file_real_constant_term = get_file("real_part_constant_term");
    FILE *file_image_constant_term = get_file("image_part_constant_term");

    complex *matrix = get_matrix(file_real_matrix, file_image_matrix);
    complex *constan_terms = get_constant_term(file_real_constant_term, file_image_constant_term);

    integer M = matrix_rows;
    integer N = matrix_columns;
    integer NRHS = 1;

    integer LDA = matrix_columns;
    integer LDB = constan_term_rows;
    integer INFO = 0;
    char TRANS = 'T';

    integer ipiv[constan_term_rows];

    const time_t time1 = time(NULL);
    cgetrf_(&M, &N, matrix, &LDA, ipiv, &INFO);
    cgetrs_(&TRANS, &N, &NRHS, matrix, &LDA, ipiv, constan_terms, &LDB, &INFO);
    const time_t time2 = time(NULL);
    printf("%ld", time2 - time1);

    save_result(constan_terms, LDB);

    return 0;
}