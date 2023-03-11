#include "controller.h"

namespace s21 {

void Controller::CountElements(char *filename, double *norm_scale) {
  modelViewer_->CountElements(filename, norm_scale);
}

void Controller::FillingMatrix(char *filename, const double *norm_scale) {
  modelViewer_->FillingMatrix(filename, norm_scale);
}

int Controller::getNumbersOfVertexesInFacet() const noexcept {
  return modelViewer_->getNumbersOfVertexesInFacet();
}

int Controller::getCountOfVertexes() const noexcept {
  return modelViewer_->getCountOfVertexes();
}

int Controller::getCountOfFacets() const noexcept {
  return modelViewer_->getCountOfFacets();
}

int Controller::getRows() const noexcept { return modelViewer_->getRows(); }

int Controller::getCols() const noexcept { return modelViewer_->getCols(); }

void Controller::ModelMove(char coord, double value) {
  modelViewer_->ModelMove(coord, value);
}

void Controller::ModelRotate(char coord, double angle) {
  modelViewer_->ModelRotate(coord, angle);
}

void Controller::ModelScale(double scale) { modelViewer_->ModelScale(scale); }

int Controller::getPolygonData(int posOfVertexInFacet) const {
  return modelViewer_->getPolygonData(posOfVertexInFacet);
}

int &Controller::getPolygonData(int posOfVertexInFacet) {
  return modelViewer_->getPolygonData(posOfVertexInFacet);
}

double Controller::getMatrixData(int row, int cols) const {
  return modelViewer_->getMatrixData(row, cols);
}

double &Controller::getMatrixData(int row, int cols) {
  return modelViewer_->getMatrixData(row, cols);
}

}  //  namespace s21
