#ifndef SRC_MODEL_S21_VIEWER_H_
#define SRC_MODEL_S21_VIEWER_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

#include "s21_matrix_oop.h"

namespace s21 {

class Model {
public:
  Model() noexcept;
  Model(int countOfVertexes, int countOfFacets, int numbersOfVertexesInFacet);
  Model(const Model &other);
  Model(Model &&other) noexcept;
  ~Model() noexcept;
  //  accessors/mutators
  int getCountOfVertexes() const noexcept;
  int getCountOfFacets() const noexcept;
  int getNumbersOfVertexesInFacet() const noexcept;
  int getRows() const noexcept;
  int getCols() const noexcept;
  int getPolygonData(int posOfVertexInFacet) const;
  int &getPolygonData(int posOfVertexInFacet);
  double getMatrixData(int row, int cols) const;
  double &getMatrixData(int row, int cols);
  void setRows(int rows);
  //  operator overloading
  bool operator==(const Model &other) const noexcept;
  Model &operator=(const Model &other) noexcept;
  static constexpr unsigned long LEN{1000};
  void CountElements(char *filename, double *norm_scale);
  void FillingMatrix(char *filename, const double *norm_scale);
  void ModelMove(char coord, double value);
  void ModelScale(double scale);
  void ModelRotate(char coord, double angle);

private:
  int countOfVertexes_;          //  количество вершин
  int countOfFacets_;            //  количество полигонов
  int numbersOfVertexesInFacet_; //  кол-во вершин для соединения
  S21Matrix matrix3d_; //  матрица с координатами вершин
  std::vector<int>
      polygon_; //  вектор с номерами вершин для попарного соединения

  bool EqData(const Model &other) const noexcept;
};

} //  namespace s21

#endif // SRC_MODEL_S21_VIEWER_H_
