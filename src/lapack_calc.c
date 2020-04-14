#include "include/lapack_calc.h"

typedef struct Data {
    float *data;
    int columns;
    int rows;
} data_struct;

const char *path_to_data_directory = "/home/kirillov/IdeaProjects/diplomaMSUJava/src/main/resources/data/";

void write_result_to_file(char *filename, float *vector_of_points, int number_of_columns, int number_of_rows);

data_struct *get_matrix_data(FILE *file);

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

data_struct *get_matrix_data(FILE *file) {
    char line[128], *p;
    int int_line[2];

    if (fgets(line, 126, file)) {
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
    float *data = malloc(sizeof(float) * m_columns * n_rows);
    int k = 0;
    while (!feof(file)) {
        if (fgets(line_, 50000, file)) {
            p_ = strtok(line_, " ");
            for (int i = 0; i < m_columns; ++i) {
                if (p_ == NULL || !strcmp(p_, "\n")) {
                    break;
                }
                sscanf(p_, "%f", &data[k++]);
                p_ = strtok(NULL, " ");
            }
        }
    }

    fclose(file);

    data_struct *result = malloc(sizeof(data_struct));
    result->data = data;
    result->columns = m_columns;
    result->rows = n_rows;

    return result;
}

/**
 * Получить матрицу с комплексными коэффициентами СЛАУ
 * @param file
 * @return
 */
complex *get_matrix(FILE *file_real_matrix, FILE *file_image_matrix) {
    data_struct *real = get_matrix_data(file_real_matrix);
    data_struct *image = get_matrix_data(file_image_matrix);

    complex *matrix = malloc(real->columns * real->rows * sizeof(complex));

    for (int i = 0; i < real->columns * real->rows; i++) {
        complex num = {real->data[i], image->data[i]};
        matrix[i] = num;
    }
    return matrix;
}

data_struct *get_const_term_data(FILE *file) {
    char line[128], *p;
    int int_line;

    if (fgets(line, 126, file)) {
        p = strtok(line, " ");
        sscanf(p, "%d", &int_line);
        p = strtok(NULL, " ");
    }

    constan_term_rows = int_line;

    char line_[128], *p_;

    float *data = malloc(sizeof(float) * int_line);
    int k = 0;
    while (!feof(file)) {
        if (fgets(line_, 126, file)) {
            p_ = strtok(line_, " ");
            if (p_ == NULL || !strcmp(p_, "\n")) {
                break;
            }
            sscanf(p_, "%f", &data[k++]);
            p_ = strtok(NULL, " ");
        }
    }

    fclose(file);

    data_struct *result = malloc(sizeof(data_struct));
    result->data = data;
    result->rows = int_line;

    return result;
}

/**
 * Получить массив свободных коэффициентов СЛАУ
 * @param file
 * @return
 */
complex *get_constant_term(FILE *file_real_constant_term, FILE *file_image_constant_term) {

    data_struct *real = get_const_term_data(file_real_constant_term);
    data_struct *image = get_const_term_data(file_image_constant_term);

    complex *vec = malloc(real->columns * sizeof(complex));

    for (int i = 0; i < real->rows; i++) {
        complex num = {real->data[i], image->data[i]};
        vec[i] = num;
    }
    return vec;
}
