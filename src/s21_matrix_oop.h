#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <stdexcept>
#include <math.h>
#include <iostream> // delete
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
        ~S21Matrix();

        // SUPPORTING FUNCTIONS

        int is_square() const{
            if (rows_ == cols_) return 1;
            return 0;
        }
        int GetRows() const{ return rows_;}
        int GetColumns() const{ return cols_;}
        void SetRows(const int rows);
        void SetColumns(const int cols);
        S21Matrix &CreateMatrix(int rows, int cols);
        void DeleteMatrix();
        S21Matrix SubMatrix(int row, int column);
        S21Matrix SubMatrix_min(int column);
        void SetElement(int row, int col, double value);
        void FillMatrix(double num);

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
        
        // OVERLOADED OPERATORS

        S21Matrix operator = (S21Matrix &other);
        S21Matrix operator = (S21Matrix&& other);
        S21Matrix operator + (const S21Matrix &other);
        S21Matrix operator - (const S21Matrix &other);
        S21Matrix operator * (const S21Matrix &other);
        S21Matrix operator * (double num);
        bool operator == (S21Matrix &other);
        void operator += (S21Matrix &other);
        void operator -= (S21Matrix &other);
        void operator *= (S21Matrix &other);
        void operator *= (double num);

        double operator()(int rows, int cols) const;
        double & operator()(int rows, int cols);
};



#endif  // S21_MATRIX_OOP_H