# Matrices_cpp
---
In this project, I implement the matrix library similiar to [**this one**](https://github.com/Enevales/s21_Matrices), but this time I used the object-oriented approach. The object-oriented approach allows to implement a library for matrices as a separate class whose objects have defined operations, that can be represented both as methods and as standard operators +, -, *, etc.

### Contents:

* [Overview](#Overview)
* [How to build](#How/to/build) 
* [Matrix operations](#Matrix/operations).
* [Technological description](#Technological/description)
* [Concepts](#Concepts)
* [Demonstration](#Demo)

### Overview:
---
Matrix structure in C language:

```cpp
class S21Matrix {
 private:
 // Attributes
 int rows_, cols_;         // Rows and columns
 double **matrix_;         // Pointer to the memory where the matrix is allocated
 public:
 S21Matrix();              // Default constructor
 ~S21Matrix();             // Destructor
 void SumMatrix(const S21Matrix& other); 
 // Other methods..
}
```

### How to build: 
---
> $ cd src
> $ make

### Matrix operations:

Matrix operations: 

| Operation | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const S21Matrix& other)` | Checks matrices for equality with each other |  |
| `void SumMatrix(const S21Matrix& other)` | Adds the second matrix to the current one | different matrix dimensions |
| `void SubMatrix(const S21Matrix& other)` | Subtracts another matrix from the current one | different matrix dimensions |
| `void MulNumber(const double num) ` | Multiplies the current matrix by a number |  |
| `void MulMatrix(const S21Matrix& other)` | Multiplies the current matrix by the second matrix | the number of columns of the first matrix is not equal to the number of rows of the second matrix |
| `S21Matrix Transpose()` | Creates a new transposed matrix from the current one and returns it |  |
| `S21Matrix CalcComplements()` | Calculates the algebraic addition matrix of the current one and returns it | the matrix is not square |
| `double Determinant()` | Calculates and returns the determinant of the current matrix | the matrix is not square |
| `S21Matrix InverseMatrix()` | Calculates and returns the inverse matrix | matrix determinant is 0 |



Constructors and destructor: 

| Method | Description |
| ----------- | ----------- |
| `S21Matrix()` | A basic constructor that initialises a matrix of some predefined dimension | 
| `S21Matrix(int rows, int cols) ` | Parametrized constructor with number of rows and columns |
| `S21Matrix(const S21Matrix& other)` | Copy constructor |
| `S21Matrix(S21Matrix&& other)` | Move constructor |
| `~S21Matrix()` | Destructor |


Overloaded operators:

| Operator | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `+`      | Addition of two matrices | different matrix dimensions |
| `-`   | Subtraction of one matrix from another | different matrix dimensions |
| `*`  | Matrix multiplication and matrix multiplication by a number | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `==`  | Checks for matrices equality (`EqMatrix`) | |
| `=`  | Assignment of values from one matrix to another one | |
| `+=`  | Addition assignment (`SumMatrix`) | different matrix dimensions |
| `-=`  | Difference assignment (`SubMatrix`) | different matrix dimensions |
| `*=`  | Multiplication assignment (`MulMatrix`/`MulNumber`) | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `(int i, int j)`  | Indexation by matrix elements (row, column) | index is outside the matrix |

### Technological description:
---
- The library was developed with C++ language of C++17 standard using gcc compiler.
- Full coverage of library functions code with unit-tests using `gtest`.

###  Demo:
---

![](materials/demo.gif)