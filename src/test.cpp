#include <gtest/gtest.h>

#include "Controller/controller.h"

s21::Model model = s21::Model();
s21::Controller controller(&model);

namespace s21 {

TEST(viewerTest, test) {
  double norm_scale = 1;
  char filename[] = "obj/test.obj";
  controller.CountElements(filename, &norm_scale);

  ASSERT_EQ(controller.getCountOfVertexes(), 3);
  ASSERT_EQ(controller.getCountOfFacets(), 1);
  ASSERT_EQ(controller.getNumbersOfVertexesInFacet(), 6);

  controller.FillingMatrix(filename, &norm_scale);

  int f[6] = {0, 1, 1, 2, 0, 2};
  for (int j = 0; j < 6; j++) {
    ASSERT_EQ(controller.getPolygonData(j), f[j]);
  }

  double filling[4][3] = {{0, 0, 0}, {0, 1, -1}, {1, 0, -1}, {1, 1, 1}};
  for (int i = 1; i < controller.getRows(); i++) {
    for (int j = 0; j < controller.getCols(); j++) {
      ASSERT_EQ(controller.getMatrixData(i, j), filling[i][j]);
    }
  }

  controller.ModelMove('x', 3);
  double move_x[4][3] = {{0, 0, 0}, {3, 1, -1}, {4, 0, -1}, {4, 1, 1}};
  for (int i = 1; i < controller.getRows(); i++) {
    for (int j = 0; j < controller.getCols(); j++) {
      ASSERT_EQ(controller.getMatrixData(i, j), move_x[i][j]);
    }
  }

  controller.ModelMove('y', 3);
  double move_y[4][3] = {{0, 0, 0}, {3, 4, -1}, {4, 3, -1}, {4, 4, 1}};
  for (int i = 1; i < controller.getRows(); i++) {
    for (int j = 0; j < controller.getCols(); j++) {
      ASSERT_EQ(controller.getMatrixData(i, j), move_y[i][j]);
    }
  }

  controller.ModelMove('z', 3);
  double move_z[4][3] = {{0, 0, 0}, {3, 4, 2}, {4, 3, 2}, {4, 4, 4}};
  for (int i = 1; i < controller.getRows(); i++) {
    for (int j = 0; j < controller.getCols(); j++) {
      ASSERT_EQ(controller.getMatrixData(i, j), move_z[i][j]);
    }
  }

  controller.ModelScale(2);
  double scale[4][3] = {{0, 0, 0}, {6, 8, 4}, {8, 6, 4}, {8, 8, 8}};
  for (int i = 1; i < controller.getRows(); i++) {
    for (int j = 0; j < controller.getCols(); j++) {
      ASSERT_EQ(controller.getMatrixData(i, j), scale[i][j]);
    }
  }

  controller.ModelRotate('x', 20);
  double rotate_x[4][3] = {{0, 0, 0},
                           {6, -0.3871245084, 8.9358902531},
                           {8, -1.2032886320, 7.1099997516},
                           {8, -4.0389055113, 10.5682185003}};
  for (int i = 1; i < controller.getRows(); i++) {
    for (int j = 0; j < controller.getCols(); j++) {
      ASSERT_NEAR(controller.getMatrixData(i, j), rotate_x[i][j], 1e-7);
    }
  }

  controller.ModelRotate('y', 20);
  double rotate_y[4][3] = {{0, 0, 0},
                           {-5.7094861967, -0.3871245084, 9.1242480230},
                           {-3.2263840114, -1.2032886320, 10.2050253640},
                           {-6.3835483940, -4.0389055113, 11.6162624011}};
  for (int i = 1; i < controller.getRows(); i++) {
    for (int j = 0; j < controller.getCols(); j++) {
      ASSERT_NEAR(controller.getMatrixData(i, j), rotate_y[i][j], 1e-7);
    }
  }

  controller.ModelRotate('z', 1);
  double rotate_z[4][3] = {{0, 0, 0},
                           {-2.7590945161, -5.0135312372, 9.1242480230},
                           {-0.7306902508, -3.3650481540, 10.2050253640},
                           {-0.0504241188, -7.5538007146, 11.6162624011}};
  for (int i = 1; i < controller.getRows(); i++) {
    for (int j = 0; j < controller.getCols(); j++) {
      ASSERT_NEAR(controller.getMatrixData(i, j), rotate_z[i][j], 1e-7);
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}  //  namespace s21
