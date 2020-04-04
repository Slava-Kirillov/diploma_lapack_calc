#include "include/lapack_calc.h"

extern int matrix_columns, matrix_rows, constan_term_rows;

#define SIZE 4

int main() {

    FILE *file_real_matrix = get_file("real_part_matrix");
    FILE *file_image_matrix = get_file("imag_part_matrix");

    FILE *file_real_constant_term = get_file("real_part_constant_term");
    FILE *file_image_constant_term = get_file("image_part_constant_term");

    complex **matrix = get_matrix(file_real_matrix, file_image_matrix);
    complex **constan_terms = get_constant_term(file_real_constant_term, file_image_constant_term);


//TODO: тестовый код для расчета СЛАУ
//######################################################################################################################
    integer M = SIZE;
    integer N = SIZE;

    integer LDA = M;
    integer INFO;

    double a[SIZE * SIZE] = {16.0, 5.0, 9.0, 4.0, 2.0, 11.0, 7.0, 14.0, 3.0, 10.0, 6.0, 15.0, 13.0, 8.0, 12.0, 1.0};

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%f ", a[i + j]);
        }
        printf("\n");
    }

    double ipiv[SIZE];
    dgetrf_(&M, &N, a, &LDA, ipiv, &INFO);

    printf("\n INFO=%d\n", INFO);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%f ", a[i + j]);
        }
        printf("\n");
    }
//######################################################################################################################

    return 0;
}