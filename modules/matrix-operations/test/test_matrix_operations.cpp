// Copyright 2020 Sokolov Andrey

#include <gtest/gtest.h>

#include <vector>

#include "include/matrix_operations.h"

#define ASSERT_NEAR_MATRIX(matrixA, matrixB, threshold) \
ASSERT_EQ(matrixA.getRows(), matrixB.getRows()); \
ASSERT_EQ(matrixA.getCols(), matrixB.getCols()); \
ASSERT_EQ(matrixA.getData().size(), matrixB.getData().size()); \
ASSERT_EQ(matrixA.getData()[0U].size(), matrixB.getData()[0U].size()); \
for (int idx{0}; idx < matrixA.getRows(); ++idx) { \
    for (int jdx{0}; jdx < matrixA.getCols(); ++jdx) { \
        ASSERT_NEAR(matrixA.getData()[idx][jdx], \
                    matrixB.getData()[idx][jdx], \
                    threshold); \
    }\
}

TEST(MatrixOperationsTest, Can_Create_Empty_Matrix) {
    // Act
    Matrix matrix(26, 12);

    // Assert
    EXPECT_EQ(26, matrix.getRows());
    EXPECT_EQ(12, matrix.getCols());
    EXPECT_NEAR(0.0, matrix.getData()[2U][3U], 0.001);
}

TEST(MatrixOperationsTest, Can_Create_Matrix) {
    // Arrange
    std::vector<std::vector<double>> data{{2.2, 1.2, 45.2, 7.1},
                                          {9.1, 2.3, 12.1, 2.3},
                                          {12.3, 4.5, 6.1, 7.9}};

    // Act
    Matrix matrix(3, 4, data);

    // Assert
    EXPECT_EQ(3, matrix.getRows());
    EXPECT_EQ(4, matrix.getCols());
    EXPECT_NEAR(7.9, matrix.getData()[2U][3U], 0.001);
}

TEST(MatrixOperationsTest, Can_Create_Via_Copying) {
    // Arrange
    std::vector<std::vector<double>> data{{2.2, 1.2, 45.2, 7.1},
                                          {9.1, 2.3, 12.1, 2.3},
                                          {12.3, 4.5, 6.1, 7.9}};
    Matrix matrix(3, 4, data);

    // Act
    Matrix copyMatrix(matrix);

    // Assert
    EXPECT_EQ(copyMatrix, matrix);
}

TEST(MatrixOperationsTest, Can_Set_Rows) {
    // Arrange
    std::vector<std::vector<double>> data{{2.2, 1.2, 45.2, 7.1},
                                          {9.1, 2.3, 12.1, 2.3},
                                          {12.3, 4.5, 6.1, 7.9}};
    Matrix matrix(3, 4, data);

    // Act
    matrix.setRows(2);

    // Assert
    EXPECT_EQ(matrix.getRows(), 2);
}

TEST(MatrixOperationsTest, Can_Set_Cols) {
    // Arrange
    std::vector<std::vector<double>> data{{2.2, 1.2, 45.2, 7.1},
                                          {9.1, 2.3, 12.1, 2.3},
                                          {12.3, 4.5, 6.1, 7.9}};
    Matrix matrix(3, 4, data);

    // Act
    matrix.setCols(2);

    // Assert
    EXPECT_EQ(matrix.getCols(), 2);
}

TEST(MatrixOperationsTest, Can_Set_Data) {
    // Arrange
    std::vector<std::vector<double>> data{{2.2, 1.2, 45.2, 7.1},
                                          {9.1, 2.3, 12.1, 2.3},
                                          {12.3, 4.5, 6.1, 7.9}};
    Matrix matrix(3, 4, data);
    std::vector<std::vector<double>> newData{{6.6, 1.2},
                                             {2.0, 5.2},
                                             {4.3, 4.1}};

    // Act
    matrix.setData(newData);

    // Assert
    EXPECT_EQ(matrix.getRows(), 3);
    EXPECT_EQ(matrix.getCols(), 2);
    EXPECT_EQ(matrix.getData(), newData);
}

TEST(MatrixOperationsTest, Can_Assign_Matrix) {
    // Arrange
    std::vector<std::vector<double>> data{{2.2, 1.2, 45.2, 7.1},
                                          {9.1, 2.3, 12.1, 2.3},
                                          {12.3, 4.5, 6.1, 7.9}};
    Matrix matrix(3, 4, data);
    Matrix copyMatrix(1, 2);

    // Act
    copyMatrix = matrix;

    // Assert
    ASSERT_NEAR_MATRIX(copyMatrix, matrix, 0.001);
}

TEST(MatrixOperationsTest, Can_Add_Matrices) {
    // Arrange
    std::vector<std::vector<double>> dataA{{0.1,   0.2,  0.3,  0.4},
                                           {1.4,   1.3,  1.2,  1.1},
                                           {1.0,   2.0,  3.0,  4.0},
                                           {11.1, 11.2, 11.3, 11.4}};

    std::vector<std::vector<double>> dataB{{0.4,   0.3,  0.2,  0.1},
                                           {1.1,   1.2,  1.3,  1.4},
                                           {2.0,   2.0,  2.0,  2.0},
                                           {10.1, 11.2, 12.3, 13.4}};

    std::vector<std::vector<double>> goldData{{0.5,   0.5,  0.5,  0.5},
                                              {2.5,   2.5,  2.5,  2.5},
                                              {3.0,   4.0,  5.0,  6.0},
                                              {21.2, 22.4, 23.6, 24.8}};

    Matrix matrixA(4, 4, dataA);
    Matrix matrixB(4, 4, dataB);

    // Act
    Matrix result = matrixA + matrixB;

    // Assert
    Matrix goldResult(4, 4, goldData);
    ASSERT_NEAR_MATRIX(result, goldResult, 0.001);
}

TEST(MatrixOperationsTest, Can_Difference_Matrices) {
    // Arrange
    std::vector<std::vector<double>> dataA{{0.1,   0.2,  0.3,  0.4},
                                           {1.4,   1.3,  1.2,  1.1},
                                           {1.0,   2.0,  3.0,  4.0},
                                           {11.1, 11.2, 11.3, 11.4}};

    std::vector<std::vector<double>> dataB{{0.4,   0.3,  0.2,  0.1},
                                           {1.1,   1.2,  1.3,  1.4},
                                           {2.0,   2.0,  2.0,  2.0},
                                           {10.1, 11.2, 12.3, 13.4}};

    std::vector<std::vector<double>> goldData{{-0.3, -0.1,  0.1,  0.3},
                                              { 0.3,  0.1, -0.1, -0.3},
                                              {-1.0,  0.0,  1.0,  2.0},
                                              { 1.0,  0.0, -1.0, -2.0}};

    Matrix matrixA(4, 4, dataA);
    Matrix matrixB(4, 4, dataB);

    // Act
    Matrix result = matrixA - matrixB;

    // Assert
    Matrix goldResult(4, 4, goldData);
    ASSERT_NEAR_MATRIX(result, goldResult, 0.001);
}

TEST(MatrixOperationsTest, Can_Matrix_Scalar_Multiplication) {
    // Arrange
    std::vector<std::vector<double>> data{{0.1,   0.2,  0.3,  0.4},
                                          {1.4,   1.3,  1.2,  1.1},
                                          {1.0,   2.0,  3.0,  4.0},
                                          {11.1, 11.2, 11.3, 11.4}};

    std::vector<std::vector<double>> goldData{{0.15,   0.3,  0.45,  0.6},
                                              { 2.1,  1.95,   1.8, 1.65},
                                              { 1.5,   3.0,   4.5,  6.0},
                                              {16.65, 16.8, 16.95, 17.1}};

    Matrix matrix(4, 4, data);

    // Act
    Matrix result = matrix * 1.5;

    // Assert
    Matrix goldResult(4, 4, goldData);
    ASSERT_NEAR_MATRIX(result, goldResult, 0.001);
}

TEST(MatrixOperationsTest, Can_Matrices_Multiplication) {
    // Arrange
    std::vector<std::vector<double>> dataA{{ 1.0, 4.0, 3.0},
                                           { 2.0, 1.0, 5.0},
                                           { 3.0, 2.0, 1.0}};

    std::vector<std::vector<double>> dataB{{ 5.0, 2.0, 1.0},
                                           { 4.0, 3.0, 2.0},
                                           { 2.0, 1.0, 5.0}};

    std::vector<std::vector<double>> goldData{{ 27.0, 17.0, 24.0},
                                              { 24.0, 12.0, 29.0},
                                              { 25.0, 13.0, 12.0}};

    Matrix matrixA(3, 3, dataA);
    Matrix matrixB(3, 3, dataB);

    // Act
    Matrix result = matrixA * matrixB;

    // Assert
    Matrix goldResult(3, 3, goldData);
    ASSERT_NEAR_MATRIX(result, goldResult, 0.001);
}

TEST(MatrixOperationsTest, Can_Matrices_Multiplication_With_Diff_Size) {
    // Arrange
    std::vector<std::vector<double>> dataA{{ 1.0, 4.0, 3.0},
                                           { 2.0, 1.0, 5.0}};

    std::vector<std::vector<double>> dataB{{ 5.0, 2.0},
                                           { 4.0, 3.0},
                                           { 2.0, 1.0}};

    std::vector<std::vector<double>> goldData{{27.0, 17.0},
                                              {24.0, 12.0}};

    Matrix matrixA(2, 3, dataA);
    Matrix matrixB(3, 2, dataB);

    // Act
    Matrix result = matrixA * matrixB;

    // Assert
    Matrix goldResult(2, 2, goldData);
    ASSERT_NEAR_MATRIX(result, goldResult, 0.001);
}

TEST(MatrixOperationsTest, Can_Take_Determinant) {
    // Arrange
    std::vector<std::vector<double>> data{{ 6.1,  2.2, -0.3,  3.4},
                                          { 1.4, 12.3,  1.2,  8.7},
                                          { 5.0,  2.0, 77.0,  6.0},
                                          {71.1, 15.7, 26.0, 12.1}};
    Matrix matrix(4, 4, data);

    // Act
    double result{matrix.determinant()};

    // Assert
    EXPECT_NEAR(result, 6080.576, 0.001);
}

TEST(MatrixOperationsTest, Can_Take_Zero_Determinant) {
    // Arrange
    std::vector<std::vector<double>> data{{0.1,   0.2,  0.3,  0.4},
                                          {1.4,   1.3,  1.2,  1.1},
                                          {1.0,   2.0,  3.0,  4.0},
                                          {11.1, 11.2, 11.3, 11.4}};
    Matrix matrix(4, 4, data);

    // Act
    double result{matrix.determinant()};

    // Assert
    EXPECT_NEAR(result, 0.0, 0.001);
}

TEST(MatrixOperationsTest, Can_Take_Determinant_With_Zero_Diag) {
    // Arrange
    std::vector<std::vector<double>> data{{ 0.0, 1.0, 0.0, 11.0},
                                          { 0.0, 0.0, 1.0, 0.0},
                                          { 0.0, 0.0, 0.0, 1.0},
                                          {99.0, 0.0, 0.0, 0.0}};
    Matrix matrix(4, 4, data);

    // Act
    double result = matrix.determinant();

    // Assert
    EXPECT_EQ(result, 99.0);
}

TEST(MatrixOperationsTest, Can_Transpose_Matrix) {
    // Arrange
    std::vector<std::vector<double>> data{{0.1,   0.2,  0.3,  0.4},
                                          {1.4,   1.3,  1.2,  1.1},
                                          {1.0,   2.0,  3.0,  4.0},
                                          {11.1, 11.2, 11.3, 11.4}};

    std::vector<std::vector<double>> goldData{{0.1, 1.4, 1.0, 11.1},
                                              {0.2, 1.3, 2.0, 11.2},
                                              {0.3, 1.2, 3.0, 11.3},
                                              {0.4, 1.1, 4.0, 11.4}};

    Matrix matrix(4, 4, data);

    // Act
    Matrix result = matrix.transpose();

    // Assert
    Matrix goldResult(4, 4, goldData);
    ASSERT_NEAR_MATRIX(result, goldResult, 0.001);
}

TEST(MatrixOperationsTest, Can_Take_Inverse_Matrix) {
    // Arrange
    std::vector<std::vector<double>> data{{-1.0,  2.0, -2.0},
                                          { 2.0, -1.0,  5.0},
                                          { 3.0, -2.0,  4.0}};
    Matrix matrix(3, 3, data);
    std::vector<std::vector<double>> goldData{{ 0.6, -0.4,  0.8},
                                              { 0.7,  0.2,  0.1},
                                              {-0.1,  0.4, -0.3}};
    Matrix goldResult(3, 3, goldData);

    // Act
    Matrix result = matrix.takeInverseMatrix();

    // Assert
    ASSERT_NEAR_MATRIX(result, goldResult, 0.001);
}

TEST(MatrixOperationsTest, Can_Not_Take_Inverse_Matrix) {
    // Arrange
    std::vector<std::vector<double>> data{{ 0.0,  2.0, -2.0},
                                          { 0.0, -1.0,  5.0},
                                          { 0.0, -2.0,  4.0}};
    Matrix matrix(3, 3, data);

    // Act & Assert
    ASSERT_ANY_THROW(matrix.takeInverseMatrix());
}

TEST(MatrixOperationsTest, Matrices_Is_Equal_To_Itself) {
    // Arrange
    std::vector<std::vector<double>> data{{0.1,   0.2,  0.3,  0.4},
                                          {1.4,   1.3,  1.2,  1.1},
                                          {1.0,   2.0,  3.0,  4.0},
                                          {11.1, 11.2, 11.3, 11.4}};
    Matrix matrix(4, 4, data);

    // Act & Assert
    EXPECT_TRUE(matrix == matrix);
}

TEST(MatrixOperationsTest, Equal_Matrices_Are_Equal) {
    // Arrange
    std::vector<std::vector<double>> dataA{{0.1,   0.2,  0.3,  0.4},
                                           {1.4,   1.3,  1.2,  1.1},
                                           {1.0,   2.0,  3.0,  4.0},
                                           {11.1, 11.2, 11.3, 11.4}};

    std::vector<std::vector<double>> dataB{{0.1,   0.2,  0.3,  0.4},
                                           {1.4,   1.3,  1.2,  1.1},
                                           {1.0,   2.0,  3.0,  4.0},
                                           {11.1, 11.2, 11.3, 11.4}};
    Matrix matrixA(4, 4, dataA);
    Matrix matrixB(4, 4, dataB);

    // Act & Assert
    EXPECT_TRUE(matrixA == matrixB);
}

TEST(MatrixOperationsTest, Not_Equal_Matrices_Rows) {
    // Arrange
    std::vector<std::vector<double>> dataA{{0.1,   0.2,  0.3},
                                           {1.4,   1.3,  1.2},
                                           {1.0,   2.0,  3.0},
                                           {11.1, 11.2, 11.3}};

    std::vector<std::vector<double>> dataB{{0.1,   0.2,  0.3,  0.4},
                                           {1.4,   1.3,  1.2,  1.1},
                                           {1.0,   2.0,  3.0,  4.0},
                                           {11.1, 11.2, 11.3, 11.4}};
    Matrix matrixA(4, 3, dataA);
    Matrix matrixB(4, 4, dataB);

    // Act & Assert
    EXPECT_FALSE(matrixA == matrixB);
}

TEST(MatrixOperationsTest, Not_Equal_Matrices_Data) {
    // Arrange
    std::vector<std::vector<double>> dataA{{0.1,   0.2,  0.3,  0.4},
                                           {1.4,   1.3,  1.2,  1.1},
                                           {1.0,   3.0,  3.0,  4.0},
                                           {11.1, 11.2, 11.3, 11.4} };

    std::vector<std::vector<double>> dataB{{0.1,   0.2,  0.3,  0.4},
                                           {1.4,   1.3,  1.2,  1.1},
                                           {1.0,   2.0,  3.0,  4.0},
                                           {11.1, 11.2, 11.3, 11.4} };
    Matrix matrixA(4, 4, dataA);
    Matrix matrixB(4, 4, dataB);

    // Act & Assert
    EXPECT_FALSE(matrixA == matrixB);
}

TEST(MatrixOperationsTest, Different_Matrices_Not_Eqal) {
    // Arrange
    std::vector<std::vector<double>> dataA{{0.1,   0.2,  0.3,  0.4},
                                           {1.4,   1.3,  1.2,  1.1},
                                           {1.0,   2.0,  3.0,  4.0},
                                           {11.1, 11.2, 11.3, 11.4} };
    std::vector<std::vector<double>> dataB{{1.1,   0.2,  0.3,  0.4},
                                           {1.4,   1.3,  2.2, 1.1},
                                           {1.0,   2.0,  3.0, 4.0},
                                           {11.1, 31.2, 11.3, 1.4} };
    Matrix matrixA(4, 4, dataA);
    Matrix matrixB(4, 4, dataB);

    // Act & Assert
    EXPECT_TRUE(matrixA != matrixB);
}
