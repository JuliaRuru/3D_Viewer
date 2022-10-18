#include "rendering_calculations.h"
#include <check.h>

START_TEST(test_viewer) {
    vertexes_t vertexes;
    data_t data;
    double norm_scale = 1;

    char *filename = "obj/test.obj";
    count_elements(filename, &data, &norm_scale);
    allocate_memory(&data, &vertexes);

    ck_assert_int_eq(data.count_of_vertexes, 3);
    ck_assert_int_eq(data.count_of_facets, 2);
    ck_assert_int_eq(data.numbers_of_vertexes_in_facet, 6);

    filling_matrix(filename, &data, &vertexes, &norm_scale);

    int f[6] = {0, 1, 1, 2, 0, 2};
    for (int j = 0; j < 6; j++) {
        ck_assert_int_eq(data.polygon[j], f[j]);
    }

    double filling[4][3] = {{0, 0, 0},
                            {0, 1, -1},
                            {1, 0, -1},
                            {1, 1, 1}};
    for (int i = 1; i < vertexes.rows; i++) {
        for (int j = 0; j < vertexes.columns; j++) {
            ck_assert_double_eq(vertexes.matrix[i][j], filling[i][j]);
        }
    }

    model_move(&vertexes, 'x', 3);
    double move_x[4][3] = {{0, 0, 0},
                           {3, 1, -1},
                           {4, 0, -1},
                           {4, 1, 1}};
    for (int i = 1; i < vertexes.rows; i++) {
        for (int j = 0; j < vertexes.columns; j++) {
            ck_assert_double_eq(vertexes.matrix[i][j], move_x[i][j]);
        }
    }

    model_move(&vertexes, 'y', 3);
    double move_y[4][3] = {{0, 0, 0},
                           {3, 4, -1},
                           {4, 3, -1},
                           {4, 4, 1}};
    for (int i = 1; i < vertexes.rows; i++) {
        for (int j = 0; j < vertexes.columns; j++) {
            ck_assert_double_eq(vertexes.matrix[i][j], move_y[i][j]);
        }
    }

    model_move(&vertexes, 'z', 3);
    double move_z[4][3] = {{0, 0, 0},
                           {3, 4, 2},
                           {4, 3, 2},
                           {4, 4, 4}};
    for (int i = 1; i < vertexes.rows; i++) {
        for (int j = 0; j < vertexes.columns; j++) {
            ck_assert_double_eq(vertexes.matrix[i][j], move_z[i][j]);
        }
    }

    model_scale(&vertexes, 2);
    double scale[4][3] = {{0, 0, 0},
                          {6, 8, 4},
                          {8, 6, 4},
                          {8, 8, 8}};
    for (int i = 1; i < vertexes.rows; i++) {
        for (int j = 0; j < vertexes.columns; j++) {
            ck_assert_double_eq(vertexes.matrix[i][j], scale[i][j]);
        }
    }

    model_rotate(&vertexes, 'x', 20);
    double rotate_x[4][3] = {{0, 0, 0},
                             {6, -0.3871245084, 8.9358902531},
                             {8, -1.2032886320, 7.1099997516},
                             {8, -4.0389055113, 10.5682185003}};
    for (int i = 1; i < vertexes.rows; i++) {
        for (int j = 0; j < vertexes.columns; j++) {
            ck_assert_float_eq(vertexes.matrix[i][j], rotate_x[i][j]);
        }
    }

    model_rotate(&vertexes, 'y', 20);
    double rotate_y[4][3] = {{0, 0, 0},
                             {-5.7094861967, -0.3871245084, 9.1242480230},
                             {-3.2263840114, -1.2032886320, 10.2050253640},
                             {-6.3835483940, -4.0389055113, 11.6162624011}};
    for (int i = 1; i < vertexes.rows; i++) {
        for (int j = 0; j < vertexes.columns; j++) {
            ck_assert_float_eq(vertexes.matrix[i][j], rotate_y[i][j]);
        }
    }

    model_rotate(&vertexes, 'z', 1);
    double rotate_z[4][3] = {{0, 0, 0},
                             {-2.7590945161, -5.0135312372, 9.1242480230},
                             {-0.7306902508, -3.3650481540, 10.2050253640},
                             {-0.0504241188, -7.5538007146, 11.6162624011}};
    for (int i = 1; i < vertexes.rows; i++) {
        for (int j = 0; j < vertexes.columns; j++) {
            ck_assert_float_eq(vertexes.matrix[i][j], rotate_z[i][j]);
        }
    }

    free_memory(&vertexes, &data);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("3D_Viewer");
    TCase *tcase_test = tcase_create("3D_Viewer_test");
    SRunner *sr = srunner_create(s1);
    int nf;
    tcase_set_timeout(tcase_test, 90);
    suite_add_tcase(s1, tcase_test);

    tcase_add_test(tcase_test, test_viewer);
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf;
}
