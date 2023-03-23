#include "s21_matrix_oop.h"

// SUPPORTING FUNCTIONS

 // Default constructor
S21Matrix::S21Matrix() : rows_(3), cols_(3) {
    CreateMatrix(rows_, cols_);
}
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
S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
    CreateMatrix(other.rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

 // Move constructor
S21Matrix::S21Matrix(S21Matrix&& other) : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;

}

 // Destructor
 S21Matrix::~S21Matrix() { DeleteMatrix(); }


void S21Matrix::CreateMatrix(int rows, int cols){
    matrix_ = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix_[i] = new double[cols]();
    }
}

void S21Matrix::DeleteMatrix(){
    if (matrix_) {
        for (int i = 0; i < rows_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
    }
}

/**
 * @brief filling matrix with gradually
 * incremented numbers, so that every
 * element is greater than one before.
 *
 * @param num starting value
*/
void S21Matrix::FillMatrix(double num){
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = num;
        num++;
        }
    }
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}


// MATRIX OPERATIONS

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
  bool is_equal = true;
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
    if ((rows_ != other.rows_) || (cols_ != other.cols_)){
        throw std::logic_error("The sizes of two matrixes are not equal!");
    }
    for (int i = 0; i < other.rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
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
    if ((rows_ != other.rows_) || (cols_ != other.cols_)){
        throw std::logic_error("The sizes of two matrixes are not equal!");
    }
    for (int i = 0; i < other.rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
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
void S21Matrix::MulMatrix(const S21Matrix& other){
    if (cols_ != other.rows_ || rows_ != other.cols_) {
        throw std::length_error("num. of columns of first matrix doesn't correspond to num. of rows of second matrix.");
    }
    S21Matrix res(rows_, other.cols_);
    for (int i = 0; i < res.rows_; i++) {
        for (int j = 0; j < res.cols_; j++) {
            for (int k = 0; k < other.rows_; k++) {
                res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    CopyMatrix(res);
    res.DeleteMatrix();
}

/**
 * @brief switches matrix rows with its columns with
 * their numbers retained
 *
 * @return 1 - matrix is invalid or allocation is failed;
 *         0 - function runs without any errors.
*/

S21Matrix S21Matrix::Transpose(){
    S21Matrix res(cols_, rows_);
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

// S21Matrix S21Matrix::CalcComplements(){
//     if(!this->is_square())
//     throw std::length_error("The matrix should be square!");
//     S21Matrix res(*this);
//     S21Matrix temp(rows_-1, cols_-1);
//     for (int i = 0; i < rows_; i++) {
//       for (int j = 0; j < cols_; j++) {
//         temp.(i, j);
//         if (temp.Determinant()) break;
//         if ((i + j + 2) % 2 != 0) res.matrix_[i][j] *= -1;
//       }

//     }
//     return res;
// }

// int s21_calc_complements(matrix_t *A, matrix_t *result) {
//   if (!valid_matrix(A)) return INCORRECT_MATRIX;
//   if (A->columns != A->rows) {
//     return CALCULATION_ERROR;
//   }
//   int error = s21_create_matrix(A->rows, A->columns, result);
//   if (!error) {
//     matrix_t temp = {0};
//     s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
//     for (int i = 0; i < A->rows; i++) {
//       for (int j = 0; j < A->columns; j++) {
//         submatrix(i, j, A, &temp);
//         if (s21_determinant(&temp, &result->matrix[i][j])) break;
//         if ((i + j + 2) % 2 != 0) result->matrix[i][j] *= -1;
//       }
//     }
//     s21_remove_matrix(&temp);
//   }
//   return error;
// }

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
    throw std::length_error("The matrix should be square!");
    double det = this->Determinant();
    if (det == 0)
    throw std::out_of_range("The determinant should be bigger than zero!");
    S21Matrix res(rows_, cols_);
    S21Matrix temp_0 = this->CalcComplements();
    S21Matrix temp_1 = this->Transpose();
    res.MulNumber(1 / det);
    return res;
}

// OVERLOADED OPERATORS

S21Matrix  S21Matrix::operator + (const S21Matrix &other){
    S21Matrix res(*this);
    res.SumMatrix(other);
    return res;
};
S21Matrix  S21Matrix::operator - (const S21Matrix &other){
    S21Matrix res(*this);
    res.SubMatrix(other);
    return res;
}
S21Matrix  S21Matrix::operator * (const S21Matrix &other){
    S21Matrix res(*this); 
    res.MulMatrix(other);
    return res;
}
S21Matrix  S21Matrix::operator * (double num){
    S21Matrix res(*this);
    res.MulNumber(num);
    return res;
}
bool  S21Matrix::operator == (S21Matrix &other){
    return EqMatrix(other); 
}

/*Заметьте, что деструктор при присвоении не вызывается. Это означает, что в реализации copy assignment
 следует освобождать старые ресурсы перед присвоением новых значений.*/
// S21Matrix &S21Matrix::operator = (S21Matrix &other){
//     if (this != &other) {
//         std::swap(rows_, other.rows_);
//         std::swap(cols_, other.cols_);
//         for (int i = 0; i < rows_; i++) {
//             for (int j = 0; j < cols_; j++) {
//                 matrix_[i][j] = other.matrix_[i][j];
//             }
//         }
//     }
//     return *this;
// }
void S21Matrix::operator = (S21Matrix&& other_matrix) {
    std::swap(*this, other_matrix);
}
void  S21Matrix::operator += (S21Matrix &other){
    SumMatrix(other);
}
void  S21Matrix::operator -= (S21Matrix &other){
    SubMatrix(other);
}
void  S21Matrix::operator *= (S21Matrix &other){
    MulMatrix(other);
}
void  S21Matrix::operator *= (double num){
    MulNumber(num);
}

double S21Matrix::operator()(int rows, int cols)const{
    if (rows >= rows_ || cols >= cols_) {
        throw std::logic_error("\nIndex out of range\n");
    }
    return matrix_[rows][cols];
}

// setting an element
double &S21Matrix::operator()(int rows, int cols) {
    if (rows >= rows_ || cols >= cols_) {
        throw std::logic_error("\nIndex out of range\n");
    }
    return matrix_[rows][cols];
}