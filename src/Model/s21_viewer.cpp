#include "s21_viewer.h"

namespace s21 {

Model::Model() noexcept : Model(0, 0, 0) {}

Model::Model(int countOfVertexes, int countOfFacets,
             int numbersOfVertexesInFacet)
    : countOfVertexes_{countOfVertexes},
      countOfFacets_{countOfFacets},
      numbersOfVertexesInFacet_{numbersOfVertexesInFacet} {
  if (countOfVertexes_ >= 1 || countOfFacets_ >= 1 ||
      numbersOfVertexesInFacet_ >= 1) {
    polygon_.resize(numbersOfVertexesInFacet_);
  }
}

Model::Model(const Model &other) : Model() {
  if (this == &other)
    throw std::out_of_range("In copy constructor: error. Incorrect data");
  *this = other;
}

Model::Model(Model &&other) noexcept : Model() {
  std::swap(countOfVertexes_, other.countOfVertexes_);
  std::swap(countOfFacets_, other.countOfFacets_);
  std::swap(numbersOfVertexesInFacet_, other.numbersOfVertexesInFacet_);
  std::swap(matrix3d_, other.matrix3d_);
  std::swap(polygon_, other.polygon_);
}

Model::~Model() noexcept { polygon_.clear(); }

int Model::getCountOfVertexes() const noexcept { return countOfVertexes_; }

int Model::getCountOfFacets() const noexcept { return countOfFacets_; }

int Model::getNumbersOfVertexesInFacet() const noexcept {
  return numbersOfVertexesInFacet_;
}

int Model::getRows() const noexcept { return matrix3d_.getRows(); }

int Model::getCols() const noexcept { return matrix3d_.getCols(); }

void Model::setRows(int rows) { matrix3d_.setRows(rows); }

double &Model::getMatrixData(int rows, int cols) {
  if (rows >= getRows() || cols >= getCols() || rows < 0 || cols < 0) {
    throw std::out_of_range("Incorrect input, index is out of range\n");
  }
  return matrix3d_(rows, cols);
}

double Model::getMatrixData(int rows, int cols) const {
  if (rows >= getRows() || cols >= getCols() || rows < 0 || cols < 0) {
    throw std::out_of_range("Incorrect input, index is out of range\n");
  }
  return matrix3d_(rows, cols);
}

int &Model::getPolygonData(int posOfVertexInFacet) {
  if (posOfVertexInFacet >= numbersOfVertexesInFacet_ ||
      posOfVertexInFacet < 0) {
    throw std::out_of_range("Incorrect input, index is out of range\n");
  }
  return polygon_[posOfVertexInFacet];
}

int Model::getPolygonData(int posOfVertexInFacet) const {
  if (posOfVertexInFacet >= numbersOfVertexesInFacet_ ||
      posOfVertexInFacet < 0) {
    throw std::out_of_range("Incorrect input, index is out of range\n");
  }
  return polygon_[posOfVertexInFacet];
}

bool Model::operator==(const Model &other) const noexcept {
  return this->EqData(other);
}

bool Model::EqData(const Model &other) const noexcept {
  if (countOfVertexes_ != other.countOfVertexes_ ||
      countOfFacets_ != other.countOfFacets_ ||
      numbersOfVertexesInFacet_ != other.numbersOfVertexesInFacet_ ||
      matrix3d_ != other.matrix3d_) {
    return false;
  } else {
    for (int i = 0; i < numbersOfVertexesInFacet_; i++) {
      if (polygon_[i] != other.polygon_[i]) {
        return false;
      }
    }
  }
  return true;
}

Model &Model::operator=(const Model &other) noexcept {
  if (this != &other) {
    polygon_.clear();
    countOfVertexes_ = other.countOfVertexes_;
    countOfFacets_ = other.countOfFacets_;
    numbersOfVertexesInFacet_ = other.numbersOfVertexesInFacet_;
    matrix3d_ = other.matrix3d_;
    polygon_ = other.polygon_;
  }
  return *this;
}

//  Метод производит подсчет вершин, ребер и количества вершин для соединения,
//  присваивает значения соответствующим атрибутам объекта.
//  Одновременно для крупных моделей подбирает такой масштаб, чтобы модель
//  полностью отображалась на экране
void Model::CountElements(char *filename, double *norm_scale) {
  countOfVertexes_ = 0;
  countOfFacets_ = 0;
  numbersOfVertexesInFacet_ = 0;
  *norm_scale = 0;
  double max_coord = 0;
  double min_coord = 0;
  FILE *file;
  file = fopen(filename, "r");
  fseek(file, 0, SEEK_SET);
  char str[Model::LEN];
  while (fgets(str, Model::LEN, file)) {
    if (str[0] == 'v' && str[1] == ' ') {
      countOfVertexes_++;
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
      countOfFacets_++;
      for (int i = 2; i < (int)strlen(str); i++) {
        if (isdigit(str[i]) && str[i - 1] == ' ') {
          numbersOfVertexesInFacet_++;
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
  setRows(countOfVertexes_);
  //  numbersOfVertexesInFacet_ увеличено вдвое потому что вершины соединяются
  //  попарно
  numbersOfVertexesInFacet_ *= 2;
}

//  Метод наполняет matrix3d координатами вершин, а polygon - перечнем пар
//  вершин, которые нужно соединить
void Model::FillingMatrix(char *filename, const double *norm_scale) {
  int count = 0;
  int row = 0;
  polygon_.clear();
  FILE *file;
  file = fopen(filename, "r");
  fseek(file, 0, SEEK_SET);
  char str[Model::LEN];
  while (fgets(str, Model::LEN, file) &&
         (int)polygon_.size() < numbersOfVertexesInFacet_) {
    if (str[0] == 'v' && str[1] == ' ') {
      row++;
      for (int i = 2, column = 0; i < (int)strlen(str); i++) {
        if (isdigit(str[i])) {
          if (str[i - 1] == '-') {
            matrix3d_(row, column) = (atof(&str[i]) * (-1)) / *norm_scale;
          } else {
            matrix3d_(row, column) = (atof(&str[i])) / *norm_scale;
          }
          column++;
          while (str[i] != ' ') i++;
        }
      }
    } else if (str[0] == 'f') {
      for (int i = 2; i < (int)strlen(str); i++) {
        if (isdigit(str[i]) && str[i - 1] == ' ') {
          polygon_.push_back(atof(&str[i]) - 1);
          count++;
          while (str[i] != ' ') i++;
          if (count % 2 == 0) {
            polygon_.push_back(polygon_[count - 1]);
            count++;
          }
        }
      }
      int copy = atof(&str[2]) - 1;
      polygon_[count - 1] = copy;
      polygon_.push_back(polygon_[count - 2]);
      count++;
    }
  }
}

void Model::ModelMove(char coord, double value) {
  int index = 3;
  if (coord == 'x') {
    index = 0;
  } else if (coord == 'y') {
    index = 1;
  } else if (coord == 'z') {
    index = 2;
  }
  for (int i = 1; i < matrix3d_.getRows(); i++) {
    matrix3d_(i, index) += value;
  }
}

void Model::ModelScale(double scale) {
  if (scale != 0) {
    for (int i = 1; i < matrix3d_.getRows(); i++) {
      for (int j = 0; j < 3; j++) {
        matrix3d_(i, j) *= scale;
      }
    }
  }
}

void Model::ModelRotate(char coord, double angle) {
  if (coord == 'x') {
    for (int i = 1; i < matrix3d_.getRows(); i++) {
      double temp_y = matrix3d_(i, 1);
      double temp_z = matrix3d_(i, 2);
      matrix3d_(i, 1) = cos(angle) * temp_y - sin(angle) * temp_z;
      matrix3d_(i, 2) = sin(angle) * temp_y + cos(angle) * temp_z;
    }
  } else if (coord == 'y') {
    for (int i = 1; i < matrix3d_.getRows(); i++) {
      double temp_x = matrix3d_(i, 0);
      double temp_z = matrix3d_(i, 2);
      matrix3d_(i, 0) = cos(angle) * temp_x - sin(angle) * temp_z;
      matrix3d_(i, 2) = sin(angle) * temp_x + cos(angle) * temp_z;
    }
  } else if (coord == 'z') {
    for (int i = 1; i < matrix3d_.getRows(); i++) {
      double temp_x = matrix3d_(i, 0);
      double temp_y = matrix3d_(i, 1);
      matrix3d_(i, 0) = cos(angle) * temp_x - sin(angle) * temp_y;
      matrix3d_(i, 1) = sin(angle) * temp_x + cos(angle) * temp_y;
    }
  }
}

}  //  namespace s21
