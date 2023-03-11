#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../Model/s21_viewer.h"

namespace s21 {

class Controller {
public:
  Controller(){};
  explicit Controller(Model *model) : modelViewer_(model) {}
  ~Controller(){};

  int getNumbersOfVertexesInFacet() const noexcept;
  int getCountOfVertexes() const noexcept;
  int getCountOfFacets() const noexcept;
  int getRows() const noexcept;
  int getCols() const noexcept;
  int getPolygonData(int posOfVertexInFacet) const;
  int &getPolygonData(int posOfVertexInFacet);
  double getMatrixData(int row, int cols) const;
  double &getMatrixData(int row, int cols);
  void CountElements(char *filename, double *norm_scale);
  void FillingMatrix(char *filename, const double *norm_scale);
  void ModelMove(char coord, double value);
  void ModelRotate(char coord, double angle);
  void ModelScale(double scale);

private:
  Model *modelViewer_;
};

} //  namespace s21

#endif //  SRC_CONTROLLER_CONTROLLER_H_
