#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <stdexcept>
#include <math.h>

#define EPS 1e-7

class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;              
        
    public:
        
        // CONSTRUCTORS & DESTRUCTORS

        S21Matrix();
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix &other);
        S21Matrix(S21Matrix&& other);
        ~S21Matrix()
        {
            // free_matrix();
        }

        // SUPPORTING FUNCTIONS

        int is_square() const{
            if (rows_ == cols_) return 1;
            return 0;
        }
        int GetRows() const{ return rows_;}
        int GetColumns() const{ return cols_;}
        void SetRows(int rows);
        void SetColumns(int cols);
        void CreateMatrix(int rows, int cols);
        void RemoveMatrix();
        S21Matrix SubMatrix(int row, int column);
        S21Matrix SubMatrix_min(int column);
        // MATRIX OPERATIONS

        bool EqMatrix(const S21Matrix& other);
        void SumMatrix(const S21Matrix& other);
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num);
        void MulMatrix(const S21Matrix& other);
        S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant();
        S21Matrix InverseMatrix();
};



#endif  // S21_MATRIX_OOP_H