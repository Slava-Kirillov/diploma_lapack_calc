#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "f2c.h"
#include "clapack.h"

const char *path_to_data_directory = "/home/kirillov/IdeaProjects/diplomaMSUJava/src/main/resources/data/";

FILE *get_file(char *filename);

complex** get_matrix(FILE *file_real_matrix, FILE *file_image_matrix);

int main() {

    FILE *file_real_matrix = get_file("real_part_matrix");
    FILE *file_image_matrix = get_file("imag_part_matrix");

    get_matrix(file_real_matrix, file_image_matrix);

//    int cgetrf_(integer *m, integer *n, complex *a, integer *lda, integer *ipiv, integer *info);
//    cgetrf_(&N, &N, matrix[0], &N, &N, &N);
    return 0;
}

/**
 * Открыть файл для чтения
 * @param filename
 * @return
 */
FILE *get_file(char *filename) {
    char *path_to_data_file = (char *) malloc(sizeof(char) * (strlen(filename) + strlen(path_to_data_directory)));

    strcat(path_to_data_file, path_to_data_directory);
    strcat(path_to_data_file, filename);

    FILE *file = fopen(path_to_data_file, "r");

    free(path_to_data_file);

    if (file == NULL) {
        perror("File reading error\n");
        exit(EXIT_FAILURE);
    }

    return file;
}

/**
 * Получить матрицу с комплексными коэффициентами
 * @param file
 * @return
 */
complex** get_matrix(FILE *file_real_matrix, FILE *file_image_matrix) {
    char line[128], *p;
    int int_line[2];

    if (fgets(line, 126, file_real_matrix)) {
        p = strtok(line, " ");
        for (int i = 0; i < 2; i++) {
            sscanf(p, "%d", &int_line[i]);
            p = strtok(NULL, " ");
        }
    }

    int m_columns = int_line[0];
    int n_rows = int_line[1];

    char line_[50000], *p_;

    complex **matrix = malloc(m_columns * n_rows * sizeof(complex));

    float *real = malloc(sizeof(float) * m_columns * n_rows);
    int k = 0;
    while (!feof(file_real_matrix)) {
        if (fgets(line_, 50000, file_real_matrix)) {
            p_ = strtok(line_, " ");
            for (int i = 0; i < m_columns; ++i) {
                if (p_ == NULL || !strcmp(p_, "\n")) {
                    break;
                }
                sscanf(p_, "%f", &real[k++]);
                p_ = strtok(NULL, " ");
            }
        }
    }

    char line__[50000], *p__;

    k = 0;
    float *image = malloc(sizeof(float) * m_columns * n_rows);
    while (!feof(file_image_matrix)) {
        if (fgets(line__, 50000, file_image_matrix)) {
            p__ = strtok(line__, " ");
            for (int i = 0; i < m_columns; ++i) {
                if (p__ == NULL || !strcmp(p__, "\n")) {
                    break;
                }
                sscanf(p__, "%f", &image[k++]);
                p__ = strtok(NULL, " ");
            }
        }
    }

    for (int i = 0; i < m_columns * n_rows; i++) {
        complex *num = malloc(sizeof(complex));
        num->r = real[i];
        num->i = image[i];

        matrix[i] = num;
    }
    return matrix;
}