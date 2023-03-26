#include <gtest/gtest.h>
#include <ostream>

#include "../s21_matrix_oop.h"

TEST(constructors, default_){
    S21Matrix x;
    S21Matrix y;
    ASSERT_EQ(x.GetRows(), 3);
    ASSERT_EQ(y.GetColumns(), 3);

    for (int i = 0; i < x.GetRows(); ++i) {
        for (int j = 0; j < x.GetColumns(); j++){
            EXPECT_EQ(x(i, j), 0) << "The matrix should be filled with zeros ";
        }
    }
}


TEST(constructors, is_square){
    S21Matrix x(3, 3);
    S21Matrix y(3, 2);
    ASSERT_EQ(x.is_square(), 1);
    ASSERT_EQ(y.is_square(), 0);
}

TEST(constructors, copy_matrix_00){
    const S21Matrix y(3, 4);
    S21Matrix copy(y);
    EXPECT_EQ(copy.GetRows(), y.GetRows());
    EXPECT_EQ(copy.GetColumns(), y.GetColumns());
}

TEST(constructors, copy_matrix_01){
    S21Matrix y(3, 4);
    y.FillMatrix(0);
    S21Matrix x(y);
    ASSERT_EQ(x.GetRows(), y.GetRows());
    ASSERT_EQ(x.GetColumns(), y.GetColumns());
    for (int i = 0; i < x.GetRows(); ++i) {
        for (int j = 0; j < x.GetColumns(); j++){
            EXPECT_EQ(x(i, j), y(i, j));
        }
    }
}

TEST(constructors, move_matrix){
    S21Matrix x = S21Matrix(5,5);
    ASSERT_EQ(x.is_square(), 1);
    ASSERT_EQ(x.GetColumns(), 5);
    ASSERT_EQ(x.GetRows(), 5);
}

TEST(support_func, set_element){
    S21Matrix x;
    double num = 1;
    for (int i = 0; i < x.GetRows(); i++) {
        for (int j = 0; j < x.GetColumns(); j++) {
        x(i, j) = num;
        num++;
        }
    }
    ASSERT_EQ(x(0,0), 1) << "Vectors x and y are of unequal length";
    ASSERT_EQ(x(0,1), 2) << "Vectors x and y are of unequal length";
    ASSERT_EQ(x(1,0), 4) << "Vectors x and y are of unequal length";
}

TEST(support_func, fill_matrix){
    S21Matrix x;
    double num = 1;
    x.FillMatrix(num);
    ASSERT_EQ(x(0,0), 1) << "Vectors x and y are of unequal length";
    ASSERT_EQ(x(0,1), 2) << "Vectors x and y are of unequal length";
    ASSERT_EQ(x(1,0), 4) << "Vectors x and y are of unequal length";
}

TEST(matrix_operations, eq_matrix_00){
    S21Matrix x(3, 3);
    S21Matrix y(3, 2);
    ASSERT_EQ(x.EqMatrix(y), 0);
    ASSERT_NE(x.EqMatrix(y), 1);
}
TEST(matrix_operations, eq_matrix_01){
    S21Matrix x(3, 3);
    x.FillMatrix(2);
    S21Matrix copy(x);
    ASSERT_EQ(copy.GetRows(), x.GetRows());
    ASSERT_EQ(copy.GetColumns(), x.GetColumns());
    ASSERT_TRUE(copy.EqMatrix(x));
    ASSERT_TRUE(x.EqMatrix(copy));
}
TEST(matrix_operations, eq_matrix_02){
    S21Matrix x(3, 3);
    x.FillMatrix(2);
    S21Matrix y(3, 3);
    x.FillMatrix(-2);
    ASSERT_FALSE(y.EqMatrix(x));
    ASSERT_FALSE(x.EqMatrix(y));
}

TEST(matrix_operations, eq_matrix_03){
    S21Matrix x(3, 3);
    x.FillMatrix(2);
    S21Matrix y(x);
    ASSERT_TRUE(y == x);
    ASSERT_TRUE(x == y);
}

TEST(matrix_operations, sum_matrix_00){
    S21Matrix x(2, 2);
    x.FillMatrix(0);
    S21Matrix y(x);
    x.SumMatrix(y);
    ASSERT_FALSE(y.EqMatrix(x));
    ASSERT_FALSE(x.EqMatrix(y));
    ASSERT_EQ(x(0, 0), 0);
    ASSERT_EQ(x(1, 0), 4);
}

TEST(matrix_operations, sum_matrix_01){
    S21Matrix x(2, 2);
    x.FillMatrix(0);
    S21Matrix y(x);
    x += y;
    ASSERT_EQ(x(0, 1), 2);
    ASSERT_EQ(x(1, 0), 4);
    S21Matrix z = x + y;
    ASSERT_EQ(z(1, 1), 9);
    ASSERT_EQ(z(1, 0), 6);
}

TEST(matrix_operations, sub_matrix_00){
    S21Matrix x(2, 2);
    x.FillMatrix(0);
    S21Matrix y(x);
    x.SubMatrix(y);
    ASSERT_EQ(x(0, 0), 0);
    ASSERT_EQ(x(0, 1), 0);
    ASSERT_EQ(x(1, 0), 0);
    ASSERT_EQ(x(1, 1), 0);
}

TEST(matrix_operations, sub_matrix_01){
    S21Matrix x(2, 2);
    x.FillMatrix(5);
    S21Matrix y(2, 2);
    y.FillMatrix(1);
    x.SubMatrix(y);
    ASSERT_EQ(x(0, 0), 4);
    ASSERT_EQ(y(0, 1), 2);
    y.SubMatrix(x);
    ASSERT_EQ(y(1, 0), -1);
    ASSERT_EQ(y(1, 1), 0);
    S21Matrix z = x - y;
    ASSERT_EQ(z(0, 0), 7);
    ASSERT_EQ(z(0, 1), 6);
}



TEST(matrix_operations, mul_number_00){
    S21Matrix x;
    x.FillMatrix(5);
    x.MulNumber(1000);
    ASSERT_EQ(x(0, 0), 5000);
    ASSERT_EQ(x(2, 1), 12000);
    x *= -1;
    ASSERT_EQ(x(0, 0), -5000);
    ASSERT_EQ(x(2, 1), -12000);
}

TEST(matrix_operations, mul_matrix_00){
    S21Matrix x(2, 3);
    x.FillMatrix(2);
    S21Matrix y(3, 2);
    y.FillMatrix(3);
    x.MulMatrix(y);
    S21Matrix check(2,2);
    check(0, 0) = 49;
    check(0, 1) = 58;
    check(1, 0) = 94;
    check(1, 1) = 112;    

    ASSERT_EQ(x.EqMatrix(check), 1);
}

TEST(matrix_operations, mul_matrix_01){
    S21Matrix x(2, 3);
    x.FillMatrix(2);
    S21Matrix y(3, 2);
    y.FillMatrix(3);
    S21Matrix res = x*y;
     
    EXPECT_EQ(res(0,0), 49);
    EXPECT_EQ(res(0,1), 58);
    EXPECT_EQ(res(1,0), 94);
    EXPECT_EQ(res(1,1), 112);

}

TEST(matrix_operations, transpose_00){
    S21Matrix x(3, 2);
    x.FillMatrix(2);
    S21Matrix res = x.Transpose();
    S21Matrix check(2,3);
    check(0, 0) = 2;
    check(0, 1) = 4;
    check(0, 2) = 6;
    check(1, 0) = 3;
    check(1, 1) = 5;
    check(1, 2) = 7;  
    ASSERT_EQ(res.EqMatrix(check), 1);
}


TEST(matrix_operations, determinant_00){
    S21Matrix x(3, 3);
    x.FillMatrix(2);
    S21Matrix y = x.Transpose();
    ASSERT_EQ(x.Determinant(), 0);
    ASSERT_EQ(y.Determinant(), 0);
}

TEST(matrix_operations, determinant_01){
    S21Matrix x(2, 2);
    x(0, 0) = 7;
    x(0, 1) = 5;
    x(1, 0) = 3;
    x(1, 1) = 9;
    ASSERT_EQ(x.Determinant(), 48);
}

TEST(matrix_operations, determinant_02){
    S21Matrix x(4, 4);
    x.FillMatrix(1);
    S21Matrix y = x.Transpose();
    y(1, 1) = 14;
    y(2, 2) = 13;
    ASSERT_EQ(y.Determinant(), -576);
}

TEST(matrix_operations, complements_00){
    S21Matrix x(2, 2);
    x(0, 0) = -666;
    x(0, 1) = -73;
    x(1, 0) = -21000;
    x(1, 1) = -36;
    S21Matrix y = x.CalcComplements();

    ASSERT_EQ(y(0, 0), -36);
    ASSERT_EQ(y(0, 1), 21000);
    ASSERT_EQ(y(1, 0), 73);
    ASSERT_EQ(y(1, 1), -666);
}

TEST(matrix_operations, complements_01){
    S21Matrix x(2, 2);
    x(0, 0) = -6;
    x(0, 1) = 7;
    x(1, 0) = 21;
    x(1, 1) = 3;
    S21Matrix y = x.CalcComplements();

    ASSERT_EQ(y(0, 0), 3);
    ASSERT_EQ(y(0, 1), -21);
    ASSERT_EQ(y(1, 0), -7);
    ASSERT_EQ(y(1, 1), -6);
}

TEST(matrix_operations, complements_02){
    S21Matrix x;
    S21Matrix y;
    x(0, 0) = 3;
    x(0, 1) = 4;
    x(0, 2) = 3;
    x(1, 0) = 1;
    x(1, 1) = 2;
    x(1, 2) = 3;
    x(2, 0) = 0;
    x(2, 1) = 7;
    x(2, 2) = 7;

    y(0, 0) = -7;
    y(0, 1) = -7;
    y(0, 2) = 7;
    y(1, 0) = -7;
    y(1, 1) = 21;
    y(1, 2) = -21;
    y(2, 0) = 6;
    y(2, 1) = -6;
    y(2, 2) = 2;

    S21Matrix res = x.CalcComplements();
    ASSERT_EQ(res.EqMatrix(y), true);
}

TEST(matrix_operations, inverse_00){
    S21Matrix x;

    x(0, 0) = 2;
    x(0, 1) = 5;
    x(0, 2) = 7;
    x(1, 0) = 6;
    x(1, 1) = 3;
    x(1, 2) = 4;
    x(2, 0) = 5;
    x(2, 1) = -2;
    x(2, 2) = -3;

    S21Matrix res = x.InverseMatrix();

    EXPECT_EQ(res(0, 0), 1);
    EXPECT_EQ(res(0, 1), -1);
    EXPECT_EQ(res(0, 2), 1);
    EXPECT_EQ(res(1, 0), -38);
    EXPECT_EQ(res(1, 1), 41);
    EXPECT_EQ(res(1, 2), -34);
    EXPECT_EQ(res(2, 0), 27);
    EXPECT_EQ(res(2, 1), -29);
    EXPECT_EQ(res(2, 2), 24);
}

// TEST(support_func, resize_00){
//     S21Matrix x;
//     x.FillMatrix(0);
//     x.SetRows(4);
//     ASSERT_EQ(x.GetRows(), 4);
//     EXPECT_EQ(x(0, 2), 2);
//     EXPECT_EQ(x(3, 0), 0);
// }

// TEST(support_func, resize_01){
//     S21Matrix x;
//     x.FillMatrix(0);
//     x.SetColumns(4);
//     ASSERT_EQ(x.GetColumns(), 4);
//     EXPECT_EQ(x(0, 2), 2);
//     EXPECT_EQ(x(1, 3), 0);
// }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
