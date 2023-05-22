#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <math.h>
#include <stdexcept>
#include <cstring>

const double EPS = 1e-7;

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  // CONSTRUCTORS & DESTRUCTORS

  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  // SUPPORTING FUNCTIONS

  void SetRows(const int &rows);
  void SetColumns(const int &cols);

  int is_square() const noexcept;
  int GetRows() const noexcept;
  int GetColumns() const noexcept;
  S21Matrix &CreateMatrix(int rows, int cols);
  void DeleteMatrix();
  S21Matrix SubmatrixMin(int row, int column) const;
  void SetElement(int row, int col, double value);
  void FillMatrix(double num);

  // MATRIX OPERATIONS

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double &num) noexcept;
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  // OVERLOADED OPERATORS

  S21Matrix operator=(S21Matrix &other);
  S21Matrix operator=(S21Matrix &&other) noexcept;
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double num);
  bool operator==(S21Matrix &other) const;
  void operator+=(S21Matrix &other);
  void operator-=(S21Matrix &other);
  void operator*=(S21Matrix &other) ;
  void operator*=(double num);

  double &operator()(int i, int j) const;
};

#endif  // S21_MATRIX_OOP_H