#include <gtest/gtest.h>
#include <ostream>

#include "../s21_matrix_oop.h"

TEST(constructors, default_){
    S21Matrix x;
    S21Matrix y;
    ASSERT_EQ(x.GetRows(), 3) << "Vectors x and y are of unequal length";
    ASSERT_EQ(y.GetColumns(), 3) << "Vectors x and y are of unequal length";
    // for (int i = 0; i < x.size(); ++i) {
    //     EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
    // }
}


TEST(constructors, is_square){
    S21Matrix x(3, 3);
    S21Matrix y(3, 2);
    ASSERT_EQ(x.is_square(), 1) << "Vectors x and y are of unequal length";
    ASSERT_EQ(y.is_square(), 0) << "Vectors x and y are of unequal length";
    // for (int i = 0; i < x.size(); ++i) {
    //     EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
    // }
}

TEST(constructors, copy_matrix_00){
    S21Matrix y(3, 4);
    S21Matrix x = y;
    ASSERT_EQ(x.is_square(), 0);
    EXPECT_EQ(x.GetRows(), y.GetRows());
    EXPECT_EQ(x.GetColumns(), y.GetColumns());
    // for (int i = 0; i < x.size(); ++i) {
    //     EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
    // }
}

TEST(constructors, copy_matrix_01){
    S21Matrix y(3, 4);
    S21Matrix x(y);
    ASSERT_EQ(x.is_square(), 0);
    EXPECT_EQ(x.GetRows(), y.GetRows());
    EXPECT_EQ(x.GetColumns(), y.GetColumns());
    // for (int i = 0; i < x.size(); ++i) {
    //     EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
    // }
}

TEST(constructors, copy_matrix_02){
    S21Matrix y(3, 4);
    S21Matrix x(y);
    y.SetRows(1); y.SetColumns(1);
    ASSERT_EQ(x.is_square(), 0);
    EXPECT_EQ(x.GetRows(), 3);
    EXPECT_EQ(x.GetColumns(), 4);
}

TEST(constructors, move_matrix){
    S21Matrix x(3, 3);
    S21Matrix y(3, 2);
    ASSERT_EQ(x.is_square(), 1) << "Vectors x and y are of unequal length";
    ASSERT_EQ(y.is_square(), 0) << "Vectors x and y are of unequal length";
    // for (int i = 0; i < x.size(); ++i) {
    //     EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
    // }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
