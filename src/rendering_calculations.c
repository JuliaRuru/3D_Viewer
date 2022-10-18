#include "rendering_calculations.h"

void count_elements(char *filename, data_t *data, double *norm_scale) {
    data->count_of_vertexes = 0;
    data->count_of_facets = 0;
    data->numbers_of_vertexes_in_facet = 0;
    *norm_scale = 0;
    double max_coord = 0;
    double min_coord = 0;
    FILE *file;
    file = fopen(filename, "r");
    fseek(file, 0, SEEK_SET);
    char str[LEN];
    while (fgets(str, LEN, file)) {               //  считываем первые N символов
        if (str[0] == 'v' && str[1] == ' ') {
            data->count_of_vertexes++;            //  подсчет количества вершин
            for (int i = 2; i < (int)strlen(str); i++) {
                if (isdigit(str[i])) {
                    if (str[i - 1] == '-') {
                        double temp_coord = atof(&str[i]) * (-1);
                        if (min_coord > temp_coord) {
                            min_coord = temp_coord;
                        }
                    } else {
                        double temp_coord = atof(&str[i]);
                        if (max_coord < temp_coord) {
                            max_coord = temp_coord;
                        }
                    }
                    while (str[i] != ' ') i++;
                }
            }
        } else if (str[0] == 'f') {
            data->count_of_facets++;              //  подсчет количества полигонов
            for (int i = 2; i < (int)strlen(str); i++) {
                if (isdigit(str[i]) && str[i-1] == ' ') {
                    data->numbers_of_vertexes_in_facet++;      //  подсчет количества вершин в полигонах
                    while (str[i] != ' ') i++;
                }
            }
        }
    }
    fclose(file);
    if (max_coord >= fabs(min_coord)) {
        *norm_scale = max_coord;
    } else {
        *norm_scale = fabs(min_coord);
    }
}

void allocate_memory(data_t *data, vertexes_t *vertexes) {
    data->polygon = (int*)malloc(2 * data->numbers_of_vertexes_in_facet * sizeof(int));
    vertexes->columns = 3;
    vertexes->rows = data->count_of_vertexes + 1;
    vertexes->matrix = (double**) malloc(vertexes->rows * sizeof(double*));
    for (int i = 0; i < vertexes->rows; i++) {
        vertexes->matrix[i] = (double*) malloc(vertexes->columns * sizeof(double));
    }
}

void filling_matrix(char *filename, data_t *data, vertexes_t *vertexes, const double *norm_scale) {
    data->numbers_of_vertexes_in_facet = 0;
    data->matrix_3d = *vertexes;
    FILE *file;
    file = fopen(filename, "r");
    fseek(file, 0, SEEK_SET);
    for (int row = 0;;) {
        char str[LEN];
        if (fgets(str, LEN, file)) {
            if (str[0] == 'v' && str[1] == ' ') {
                row++;
                for (int i = 2, column = 0; i < (int)strlen(str); i++) {
                    if (isdigit(str[i])) {
                        if (str[i - 1] == '-') {
                            vertexes->matrix[row][column] = (atof(&str[i]) * (-1)) / *norm_scale;
                        } else {
                            vertexes->matrix[row][column] = (atof(&str[i])) / *norm_scale;
                        }
                        column++;
                        while (str[i] != ' ') i++;
                    }
                }
            } else if (str[0] == 'f') {
                for (int i = 2; i < (int)strlen(str); i++) {
                    if (isdigit(str[i]) && str[i-1] == ' ') {
                        data->polygon[data->numbers_of_vertexes_in_facet] = atof(&str[i]) - 1;
                        data->numbers_of_vertexes_in_facet++;
                        while (str[i] != ' ') i++;
                        if (data->numbers_of_vertexes_in_facet % 2 == 0) {
                            data->polygon[data->numbers_of_vertexes_in_facet] =
                            data->polygon[data->numbers_of_vertexes_in_facet - 1];
                            data->numbers_of_vertexes_in_facet++;
                        }
                    }
                }
                int copy = atof(&str[2]) - 1;
                data->polygon[data->numbers_of_vertexes_in_facet - 1] = copy;
                data->polygon[data->numbers_of_vertexes_in_facet] =
                data->polygon[data->numbers_of_vertexes_in_facet - 2];
                data->numbers_of_vertexes_in_facet++;
            }
        } else {
            break;
        }
    }
}

void free_memory(vertexes_t *vertexes, data_t *data) {
    for (int i = 0; i < vertexes->rows; i++) {
        free(vertexes->matrix[i]);
    }
    free(vertexes->matrix);
    free(data->polygon);
}

void model_move(vertexes_t *vertexes, char coord, double value) {
    int index;
    if (coord == 'x') {
        index = 0;
    } else if (coord == 'y') {
        index = 1;
    } else if (coord == 'z') {
        index = 2;
    }
    for (int i = 1; i < vertexes->rows; i++) {
        vertexes->matrix[i][index] += value;
    }
}

void model_scale(vertexes_t *vertexes, double scale) {
    if (scale != 0) {
        for (int i = 1; i < vertexes->rows; i++) {
            for (int j = 0; j < 3; j++) {
                vertexes->matrix[i][j] *= scale;
            }
        }
    }
}

void model_rotate(vertexes_t *vertexes, char coord, double angle) {
    if (coord == 'x') {
        for (int i = 1; i < vertexes->rows; i++) {
            double temp_y = vertexes->matrix[i][1];
            double temp_z = vertexes->matrix[i][2];
            vertexes->matrix[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
            vertexes->matrix[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
        }
    } else if (coord == 'y') {
        for (int i = 1; i < vertexes->rows; i++) {
            double temp_x = vertexes->matrix[i][0];
            double temp_z = vertexes->matrix[i][2];
            vertexes->matrix[i][0] = cos(angle) * temp_x - sin(angle) * temp_z;
            vertexes->matrix[i][2] = sin(angle) * temp_x + cos(angle) * temp_z;
        }
    } else if (coord == 'z') {
        for (int i = 1; i < vertexes->rows; i++) {
            double temp_x = vertexes->matrix[i][0];
            double temp_y = vertexes->matrix[i][1];
            vertexes->matrix[i][0] = cos(angle) * temp_x - sin(angle) * temp_y;
            vertexes->matrix[i][1] = sin(angle) * temp_x + cos(angle) * temp_y;
        }
    }
}
