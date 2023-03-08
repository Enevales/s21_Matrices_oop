#include "s21_matrix_oop.h"

 // Default constructor
S21Matrix::S21Matrix() {
    rows_ = 3;
    cols_ = 3;
}
 // Parametrized constructor with number of rows and columns
S21Matrix::S21Matrix(int rows, int cols) {
    if (rows < 1 || cols < 1) {
        throw std::out_of_range("Wrong size of matrix!");
    }
    rows_ = rows;
    cols_ = cols;
    
}

 // Copy constructor
S21Matrix::S21Matrix(const S21Matrix &other){
    rows_ = other.rows_;
    cols_ = other.cols_;
    // ...
    // CopyArray(other.A, other.count); 
}

 // Move constructor
S21Matrix::S21Matrix(S21Matrix&& other){
    rows_ = other.rows_;
    cols_ = other.cols_;
    // ...
    // CopyArray(other.A, other.count);
    other.rows_ = 0;
    other.cols_ = 0;

}

 // Destructor

void S21Matrix::SetRows(int rows){
    if (rows < 1){
        throw std::out_of_range("Wrong number of rows!");
    } 
    rows_ = rows;
}
void S21Matrix::SetColumns(int cols){
    if (cols < 1){
        throw std::out_of_range("Wrong number of columns!");
    } 
    cols_ = cols;
}

void S21Matrix::CreateMatrix(int rows, int cols){
    matrix_ = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix_[i] = new double[cols]();
    }
}

void S21Matrix::RemoveMatrix(){
    if (matrix_) {
        for (int i = 0; i < rows_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
    }
}

/**
 * @brief creates n-1 order mattrix in
 * which it stores matrix created by
 * deleting given row and column.
 *
 * @param row - certain row from a larger matrix
 * that is not going to end in the resulting matrix.
 * @param column - certain column from a larger matrix
 * that is not going to end in the resulting matrix.
*/
S21Matrix S21Matrix::SubMatrix(int row, int column) {
    S21Matrix sub(rows_-1, cols_-1);
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

/**
 * @brief compares two matrices element
 * by element. Comparison is up to and
 * including 7 decimal places.
 *
 * @return TRUE (1) if matrices are equal.
 * FALSE (0) if matrices are not equal.
*/

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool is_equal = false;
  if ((rows_ == other.rows_) && (cols_ == other.cols_)) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) return false;
      }
    }
  } else {
    is_equal = false;
  }
  return is_equal;
}

/**
 * @brief The sum of two matrices.
 * @return 1 - matrix A  or B is invalid;
           2 - number of rows or/and columns of first
 * matrix isn't equal to number of rows & columns of second
 * matrix.
 *         0 - function runs without any errors.
*/
void S21Matrix::SumMatrix(const S21Matrix& other){
    if ((rows_ == other.rows_) || (cols_ == other.cols_)){
        throw std::out_of_range("The sizes of two matrixes are not equal!");
    }
    for (int i = 0; i < other.rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            other.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
        }
    }
}

/**
 * @brief subtracting matrices.
 * @return 1 - matrix A  or B is invalid;
           2 - number of rows or/and columns of first
 * matrix isn't equal to number of rows & columns of second
 * matrix.
 *         0 - function runs without any errors.
*/
void S21Matrix::SubMatrix(const S21Matrix& other) {
    if ((rows_ == other.rows_) || (cols_ == other.cols_)){
        throw std::out_of_range("The sizes of two matrixes are not equal!");
    }
    for (int i = 0; i < other.rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            other.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
        }
    }
}

/**
 * @brief Scalar multiplication.
 * Each element is multiplied by a scalar value.
 * @param number - double value we multiply with matrix.
 * @return 1 - matrix A is invalid or allocation is failed;
 *         0 - function runs without any errors.
*/
void  S21Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] * num;
        }
    }
}

/**
 * @brief Multiplication of two matrices.
 * Multiplying each element of the column of the
 * first matrix with each element of rows of the
 * second matrix and add them all.
 *
 * @return 1 - matrix A or matrix B is invalid;
 *         2 - num. of columns of first matrix doesn't correspond
 * to num. of rows of second matrix.
 *         0 - function runs without any errors.
*/
// void S21Matrix::MulMatrix(const S21Matrix& other){
//     // ..
// }

/**
 * @brief switches matrix rows with its columns with
 * their numbers retained
 *
 * @return 1 - matrix is invalid or allocation is failed;
 *         0 - function runs without any errors.
*/

S21Matrix S21Matrix::Transpose(){
    S21Matrix res(*this);
    for (int i = 0; i < res.rows_; i++) {
      for (int j = 0; j < res.cols_; j++) {
        res.matrix_[i][j] = matrix_[j][i];
      }
    }
  return res;
}

S21Matrix S21Matrix::SubMatrix_min(int column) {
  int m = 0;
  int n = 0;
  S21Matrix res((this->rows_)-1, (this->cols_)-1);
  for (int i = 1; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
        if (j == column) continue;
        res.matrix_[m][n] = matrix_[i][j];
        n++;
        if (n == res.cols_) n = 0;
    }
    m++;
  }
  return res;
}

/**
 * @brief recursive function, that finds
 * a determinant of a square matrix. It refers
 * to itself, if order of a given matrix is
 * greater than 2.
 *
 * @return 1 - matrix is invalid;
 *         2 - matrix is not square (if matrix)
 * doesn't have same number of rows & columns;
 *         0 - function runs without any errors.
*/
double S21Matrix::Determinant() {
    if(!this->is_square())
    throw std::out_of_range("The matrix should be square!");
    
    double det = 0;
    double det_temp = 0;
    int order = rows_;
    if (order == 1) {
        det = matrix_[0][0];
    } else if (order == 2) {
        det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    } else if (order > 2) {
        for (int i = 0; i < order; i++) {
            S21Matrix temp = SubMatrix_min(i);
            det_temp = temp.Determinant();
            if ((i % 2) != 0) det_temp *= -1;
            det += matrix_[0][i] * det_temp;
      }
  }
  return det;
}
/**
 * @brief find the matrix of algebraic complements
 * of a given SQUARE matrix by finding minor of each element,
 * (determinant of a submatrix obtained by deleting out the
 * i-th row and the j-th column) and multiplying each
 * minor by -1^(i+j)
 *
 * @return 1 - matrix is invalid or allocation is failed;
 *         2 - given matrix isn't square.
 *         0 - function runs without any errors.
*/

S21Matrix S21Matrix::CalcComplements(){
    if(!this->is_square())
    throw std::out_of_range("The matrix should be square!");
    S21Matrix res(*this);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix temp = SubMatrix(i, j);
        if (temp.Determinant()) break;
        if ((i + j + 2) % 2 != 0) res.matrix_[i][j] *= -1;
      }
    }
    return res;
}


/**
 * @brief finds inverse of a square matrix
 * by constructing matrix of algebraic
 * complements, then transposing it and multiplying
 * each element of a matrix by 1/det(A).
 *
 * @return 1 - matrix is invalid;
 *         2 - matrix is not square (if matrix)
 * doesn't have same number of rows & columns or determinant of a matrix is
 ZERO;
 *         0 - function runs without any errors.
*/

S21Matrix S21Matrix::InverseMatrix() {
    if(!this->is_square())
    throw std::out_of_range("The matrix should be square!");
    double det = this->Determinant();
    if (det == 0)
    throw std::out_of_range("The determinant should be bigger than zero!");
    S21Matrix res(rows_, cols_);
    S21Matrix temp_0 = this->CalcComplements();
    S21Matrix temp_1 = this->Transpose();
    res.MulNumber(1 / det);
    return res;
}