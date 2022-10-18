#ifndef SRC_RENDERING_CALCULATIONS_H_
#define SRC_RENDERING_CALCULATIONS_H_

#define LEN 1000

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vertexes {
    double **matrix;
    int rows;               //  количество рядов = количеству вершин +1
    int columns;            //  количество колонок 3 (x, y, z)
} vertexes_t;

typedef struct data {
    int count_of_vertexes;  //  количество вершин
    int count_of_facets;    //  количество полигонов
    int numbers_of_vertexes_in_facet;   //  кол-во вершин для соединения
    vertexes_t matrix_3d;   //  матрица с координатами вершин
    int *polygon;           //  массив номеров вершин, которые мы будем хранить для соединений
} data_t;

void count_elements(char *filename, data_t *data, double *norm_scale);
void allocate_memory(data_t *data, vertexes_t *vertexes);
void filling_matrix(char *filename, data_t *data, vertexes_t *vertexes, const double *norm_scale);
void model_move(vertexes_t *vertexes, char coord, double value);
void model_scale(vertexes_t *vertexes, double scale);
void model_rotate(vertexes_t *vertexes, char coord, double angle);
void free_memory(vertexes_t *vertexes, data_t *data);

#endif  // SRC_RENDERING_CALCULATIONS_H_
