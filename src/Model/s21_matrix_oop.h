#ifndef SRC_MODEL_S21_MATRIX_OOP_H_
#define SRC_MODEL_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

namespace s21 {

class S21Matrix {
public:
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  //  accessors
  int getRows() const;
  int getCols() const;

  //  mutators
  void setRows(int rows);
  void setCols(int cols);

  //  public methods
  bool Eq_matrix(const S21Matrix &other) const;
  void Sum_matrix(const S21Matrix &other);
  void Sub_matrix(const S21Matrix &other);
  void Mul_number(const double num);
  void Mul_matrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix Calc_complements() const;
  S21Matrix Inverse_matrix() const;
  void Print_matrix();
  static constexpr double EPS{1e-7};

  //  operator overloading
  bool operator==(const S21Matrix &other) const;
  bool operator!=(const S21Matrix &other) const noexcept;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);
  double operator()(int row, int cols) const;
  double &operator()(int row, int cols);

private:
  int rows_, cols_; //  rows and columns attributes
  double **matrix_; //  pointer to the memory where the matrix will be allocated

  void CreateMatrix(int rows, int cols);
  void DeleteMatrix();
  void CopyMatrix(const S21Matrix &other);
  S21Matrix MinorMatrix(int row, int col) const;
};

S21Matrix operator+(const S21Matrix &left, const S21Matrix &right);
S21Matrix operator-(const S21Matrix &left, const S21Matrix &right);
S21Matrix operator*(const S21Matrix &left, const S21Matrix &right);
S21Matrix operator*(const S21Matrix &left, const double num);
S21Matrix operator*(const double num, const S21Matrix &right);

} // namespace s21

#endif //  SRC_MODEL_S21_MATRIX_OOP_H_
