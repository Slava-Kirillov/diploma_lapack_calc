#include "include/lapack_calc.h"

const char *path_to_data_directory = "/home/kirillov/IdeaProjects/diplomaMSUJava/src/main/resources/data/";

void write_result_to_file(char *filename, float *vector_of_points, int number_of_columns, int number_of_rows);

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

void save_result(complex *constant_terms, int length) {
    float real[length];
    float imag[length];

    for (int i = 0; i < length; i++) {
        real[i] = constant_terms[i].r;
        imag[i] = constant_terms[i].i;
    }

    write_result_to_file("real_result", real, 1, length);
    write_result_to_file("imag_result", imag, 1, length);
}

/**
 * Печать результата в файл
 * @param filename
 * @param vector_of_points
 * @param number_of_columns
 * @param number_of_rows
 */
void write_result_to_file(char *filename, float *vector_of_points, int number_of_columns, int number_of_rows) {
    char *path_to_data_file = malloc(sizeof(char) * (strlen(filename) + strlen(path_to_data_directory)));
    memset(path_to_data_file, 0, sizeof(char) * (strlen(filename) + strlen(path_to_data_directory)));

    strcat(path_to_data_file, path_to_data_directory);
    strcat(path_to_data_file, filename);

    FILE *file = fopen(path_to_data_file, "w");

    if (file == NULL) {
        perror(path_to_data_file);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d\n", number_of_rows);

    for (int i = 0; i < number_of_rows; ++i) {
        for (int j = 0; j < number_of_columns; ++j) {
            fprintf(file, "%f ", *vector_of_points);
            vector_of_points++;
        }
        fprintf(file, "%s", "\n");
    }

    fclose(file);
}

/**
 * Получить матрицу с комплексными коэффициентами СЛАУ
 * @param file
 * @return
 */
complex *get_matrix(FILE *file_real_matrix, FILE *file_image_matrix) {
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

    matrix_columns = m_columns;
    matrix_rows = n_rows;

    char line_[50000], *p_;

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

    fclose(file_real_matrix);

    char line__[50000], *p__;

    k = 0;
    float *image = malloc(sizeof(float) * m_columns * n_rows);
    fgets(line__, 50000, file_image_matrix);
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

    fclose(file_image_matrix);

    complex *matrix = malloc(m_columns * n_rows * sizeof(complex));

    for (int i = 0; i < m_columns * n_rows; i++) {
        complex num = {real[i], image[i]};
        matrix[i] = num;
    }
    return matrix;
}

/**
 * Получить массив свободных коэффициентов СЛАУ
 * @param file
 * @return
 */
complex *get_constant_term(FILE *file_real_constant_term, FILE *file_image_constant_term) {
    char line[128], *p;
    int int_line;

    if (fgets(line, 126, file_real_constant_term)) {
        p = strtok(line, " ");
        sscanf(p, "%d", &int_line);
        p = strtok(NULL, " ");
    }

    constan_term_rows = int_line;

    char line_[128], *p_;

    float *real = malloc(sizeof(float) * int_line);
    int k = 0;
    while (!feof(file_real_constant_term)) {
        if (fgets(line_, 126, file_real_constant_term)) {
            p_ = strtok(line_, " ");
            if (p_ == NULL || !strcmp(p_, "\n")) {
                break;
            }
            sscanf(p_, "%f", &real[k++]);
            p_ = strtok(NULL, " ");
        }
    }

    fclose(file_real_constant_term);

    char line__[128], *p__;

    k = 0;
    float *image = malloc(sizeof(float) * int_line);

    fgets(line__, 126, file_image_constant_term);
    while (!feof(file_image_constant_term)) {
        if (fgets(line__, 126, file_image_constant_term)) {
            p__ = strtok(line__, " ");
            if (p__ == NULL || !strcmp(p__, "\n")) {
                break;
            }
            sscanf(p__, "%f", &image[k++]);
            p__ = strtok(NULL, " ");
        }
    }

    fclose(file_image_constant_term);

    complex *vec = malloc(int_line * sizeof(complex));

    for (int i = 0; i < int_line; i++) {
        complex num = {real[i], image[i]};
        vec[i] = num;
    }
    return vec;
}
