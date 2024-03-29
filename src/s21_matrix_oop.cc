#include "s21_matrix_oop.h"

// CONSTRUCTORS AND DESTRUCTOR ---------------------------

// Default constructor
S21Matrix::S21Matrix() : rows_(3), cols_(3) { CreateMatrix(rows_, cols_); }

// Parametrized constructor with number of rows and columns
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::out_of_range("Wrong size of matrix!");
  }
  rows_ = rows;
  cols_ = cols;
  CreateMatrix(rows_, cols_);
}

// Copy constructor
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Move constructor
S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// Destructor
S21Matrix::~S21Matrix() { DeleteMatrix(); }

S21Matrix &S21Matrix::CreateMatrix(int rows, int cols) {
  matrix_ = new double *[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols]();
  }
  return *this;
}

void S21Matrix::DeleteMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

// ACCESSORS AND MUTATORS ---------------------------

void S21Matrix::SetRows(const int &rows) {
  if (rows <= 0)
    throw std::length_error("The number of rows must be greater than zero!");
  S21Matrix res(rows, cols_);
  for (int i = 0; i < std::min(rows_, rows); i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = matrix_[i][j];
    }
  }
  DeleteMatrix();
  *this = std::move(res);
}

void S21Matrix::SetColumns(const int &cols) {
  if (cols <= 0)
    throw std::length_error("The number of rows must be greater than zero!");

  S21Matrix res(rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < std::min(cols_, cols); j++) {
      res.matrix_[i][j] = matrix_[i][j];
    }
  }
  DeleteMatrix();
  *this = std::move(res);
}

int S21Matrix::GetRows() const noexcept { return rows_; }
int S21Matrix::GetColumns() const noexcept { return cols_; }

// SUPPORTING FUNCTIONS ---------------------------

void S21Matrix::FillMatrix(double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = num;
      num++;
    }
  }
}

int S21Matrix::is_square() const noexcept {
  return (rows_ == cols_);
}

// MATRIX OPERATIONS ---------------------------

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool is_equal = true;
  if ((rows_ == other.rows_) && (cols_ == other.cols_)) {
    for (int i = 0; i < rows_ && is_equal == true; i++) {
      for (int j = 0; j < cols_ && is_equal == true; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) is_equal = false;
      }
    }
  } else {
    is_equal = false;
  }
  return is_equal;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    throw std::logic_error("The sizes of two matrixes are not equal!");
  }
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    throw std::logic_error("The sizes of two matrixes are not equal!");
  }
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double &num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_ || rows_ != other.cols_) {
    throw std::logic_error(
        "num. of columns of first matrix doesn't correspond to num. of rows of "
        "second matrix.");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < res.rows_; i++) {
    for (int j = 0; j < res.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = res;
}

S21Matrix S21Matrix::Transpose() const{
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < res.rows_; i++) {
    for (int j = 0; j < res.cols_; j++) {
      res.matrix_[i][j] = matrix_[j][i];
    }
  }
  return res;
}

// a matrix formed from parts of a larger matrix
S21Matrix S21Matrix::SubmatrixMin(int row, int column) const{
  S21Matrix sub(rows_ - 1, cols_ - 1);
  int m = 0;
  int n = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == row) continue;
    for (int j = 0; j < cols_; j++) {
      if (j == column) continue;
      sub.matrix_[m][n] = matrix_[i][j];
      n++;
      if (n == sub.cols_) n = 0;
    }
    m++;
  }
  return sub;
}

double S21Matrix::Determinant() const{
  if (!this->is_square())
    throw std::length_error("The matrix should be square!");

  double det = 0;
  double det_temp = 0;
  int order = rows_;
  if (order == 1) {
    det = matrix_[0][0];
  } else if (order == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else if (order > 2) {
    for (int i = 0; i < order; i++) {
      S21Matrix temp = SubmatrixMin(0, i);
      det_temp = temp.Determinant();
      if ((i % 2) != 0) det_temp *= -1;
      det += matrix_[0][i] * det_temp;
    }
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() const{
  if (!this->is_square())
    throw std::length_error("The matrix should be square!");
  if (this->Determinant() == 0)
    throw std::logic_error("The determinant shouldn't be equal to zero!");
  S21Matrix res(*this);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix temp = SubmatrixMin(i, j);
      res.matrix_[i][j] = temp.Determinant();
      if ((i + j + 2) % 2 != 0) res.matrix_[i][j] *= -1;
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() const{
  if (!this->is_square())
    throw std::length_error("The matrix should be square!");
  double det = this->Determinant();
  if (det == 0)
    throw std::logic_error("The determinant should be greater than zero!");
  if (rows_ == 1 && cols_ == 1) return *this;
  S21Matrix temp = this->CalcComplements();
  S21Matrix res = temp.Transpose();
  res.MulNumber(1 / det);
  return res;
}

// OVERLOADED OPERATORS ---------------------------

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
};
S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}
S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}
S21Matrix S21Matrix::operator*(double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

bool S21Matrix::operator==(S21Matrix &other) const { return EqMatrix(other); }

S21Matrix S21Matrix::operator=(S21Matrix &other) {
  SetRows(other.rows_);
  SetColumns(other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

// assignment operator that will accept a temporary rvalue object.

S21Matrix S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    DeleteMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

void S21Matrix::operator+=(S21Matrix &other) { SumMatrix(other); }
void S21Matrix::operator-=(S21Matrix &other) { SubMatrix(other); }
void S21Matrix::operator*=(S21Matrix &other) { MulMatrix(other); }
void S21Matrix::operator*=(double num) { MulNumber(num); }

double &S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_) {
    throw std::out_of_range("\nIndex out of range\n");
  }
  return matrix_[i][j];
}