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
        x.SetElement(i, j, num);
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


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
