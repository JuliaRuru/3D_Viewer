#include "s21_matrix_oop.h"

namespace s21 {

//  ========================== Constructors ==========================
S21Matrix::S21Matrix() noexcept : S21Matrix(0, 3) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_{ rows + 1 }, cols_{ cols } {
  if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("In constructor with parameters: rows or cols < 0\n");
  }
  CreateMatrix(rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix& other) : S21Matrix() {
  if (this == &other) throw std::out_of_range("In copy constructor: error. Incorrect data");
  *this = other;
}

S21Matrix::S21Matrix(S21Matrix&& other) : rows_{ 0 }, cols_{ 0 }, matrix_{ nullptr } {
  std::swap(matrix_, other.matrix_);
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
}

S21Matrix::~S21Matrix() {
  DeleteMatrix();
}

//  =========================== Getters/Setters =======================
int S21Matrix::getRows() const {
  return rows_;
}

int S21Matrix::getCols() const {
  return cols_;
}

void S21Matrix::setRows(int rows) {
  if (rows < 1) {
    throw std::invalid_argument("In mutator setRows: rows must be > 0\n");
  }
  S21Matrix temp_matrix(rows, cols_);
  int min_rows = rows_;
  if (rows < rows_) {
    min_rows = rows;
  }
  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < cols_; j++) {
      temp_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = temp_matrix;
}

void S21Matrix::setCols(int cols) {
  if (cols < 1) {
    throw std::invalid_argument("In mutator setCols: cols must be > 0\n");
  }
  S21Matrix temp_matrix(rows_, cols);
  int min_cols = cols_;
  if (cols < cols_) {
    min_cols = cols;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < min_cols; j++) {
      temp_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = temp_matrix;
}

//  ======================== Operations with matrices ===================
bool S21Matrix::Eq_matrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
          return false;
        }
      }
    }
  }
  return true;
}

void S21Matrix::Sum_matrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("In method sum_matrix: matrices have a different size\n");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::Sub_matrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("In method sub_matrix: matrices have a different size\n");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::Mul_number(const double num) {
  if (std::isnan(num) || std::isinf(num)) {
    throw std::out_of_range("In method mul_number: incorrect value of number\n");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::Mul_matrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::domain_error("In method mul_matrix: rows of first matrix != cols of second matrix\n");
  }
  S21Matrix matrix_temp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        matrix_temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = matrix_temp;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix matrix_result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return matrix_result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::domain_error("In method determinant: rows != cols\n");
  }
  double result { 0 };
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = (matrix_[0][0] * matrix_[1][1]) - (matrix_[1][0] * matrix_[0][1]);
  } else {
    for (int i = 0; i < rows_; i++) {
      S21Matrix minor = MinorMatrix(0, i);
      result += (i % 2 ? -1 : 1) * matrix_[0][i] * minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::Calc_complements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("In method calc_complements: rows != cols\n");
  }
  S21Matrix matrix_result(*this);
  for (int i = 0; i < matrix_result.rows_; i++) {
    for (int j = 0; j < matrix_result.cols_; j++) {
      S21Matrix minor = MinorMatrix(i, j);
      double det = minor.Determinant();
      matrix_result.matrix_[i][j] = pow(-1, i+j) * det;
    }
  }
  return matrix_result;
}

S21Matrix S21Matrix::Inverse_matrix() const {
  double det = Determinant();
  if (det == 0) {
    throw std::domain_error("In method inverse_matrix: determinant = 0\n");
  }
  S21Matrix matrix_result(rows_, cols_);
  S21Matrix complements = Calc_complements();
  S21Matrix trans = complements.Transpose();
  for (int i = 0; i < trans.rows_; i++) {
    for (int j = 0; j < trans.cols_; j++) {
      matrix_result.matrix_[i][j] = trans.matrix_[i][j] / det;
    }
  }
  return matrix_result;
}

//  ======================== Operator overloading ========================
S21Matrix operator+(const S21Matrix& left, const S21Matrix& right) {
    S21Matrix result(left);
    return result += right;
}

S21Matrix operator-(const S21Matrix& left, const S21Matrix& right) {
    S21Matrix result(left);
    return result -= right;
}

S21Matrix operator*(const S21Matrix& left, const S21Matrix& right) {
    S21Matrix result(left);
    return result *= right;
}

S21Matrix operator*(const S21Matrix& left, const double num) {
    S21Matrix result(left);
    return result *= num;
}

S21Matrix operator*(const double num, const S21Matrix& right) {
    S21Matrix result(right);
    return result *= num;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
    return this->Eq_matrix(other);
}

bool S21Matrix::operator!=(const S21Matrix& other) const noexcept {
  return !this->Eq_matrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this != &other) {
        DeleteMatrix();           //  на случай, если матрица2 > матрицы1, чтобы выделить память
        rows_ = other.rows_;
        cols_ = other.cols_;
        CreateMatrix(rows_, cols_);
        CopyMatrix(other);
    }
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    Sum_matrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    Sub_matrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
    Mul_number(num);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    Mul_matrix(other);
    return *this;
}

double& S21Matrix::operator()(int rows, int cols) {
    if (rows >= rows_ || cols >= cols_ || rows < 0 || cols < 0) {
        throw std::out_of_range("Incorrect input, index is out of range\n");
    }
    return matrix_[rows][cols];
}

double S21Matrix::operator()(int rows, int cols) const {
    if (rows >= rows_ || cols >= cols_ || rows < 0 || cols < 0) {
        throw std::out_of_range("Incorrect input, index is out of range\n");
    }
    return matrix_[rows][cols];
}

//  ============================= Helpers =============================
void S21Matrix::CreateMatrix(int rows, int cols) {
    matrix_ = new double* [rows];
    for (int i = 0; i < rows; i++) {
        matrix_[i] = new double[cols]{ 0 };
    }
}

void S21Matrix::DeleteMatrix() {
    if (matrix_) {
        for (int i = 0; i < rows_; ++i) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
    }
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

S21Matrix S21Matrix::MinorMatrix(int row, int col) const {
    S21Matrix minor(rows_ - 1, cols_ - 1);
    for (int i = 0; i < minor.rows_; i++) {
        for (int j = 0; j < minor.cols_; j++) {
            if (i >= row && j >= col) {
                minor.matrix_[i][j] = matrix_[i+1][j+1];
            } else if (i >= row) {
                minor.matrix_[i][j] = matrix_[i+1][j];
            } else if (j >= col) {
                minor.matrix_[i][j] = matrix_[i][j+1];
            } else {
                minor.matrix_[i][j] = matrix_[i][j];
            }
        }
    }
    return minor;
}

void S21Matrix::Print_matrix() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << matrix_[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "rows = " << rows_ << "\n";
    std::cout << "cols = " << cols_ << "\n";
}

}  //  namespace s21
