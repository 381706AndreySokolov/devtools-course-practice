// Copyright 2020 Sokolov Andrey
#include <vector>
#include <algorithm>
#include "include/matrix_operations.h"


Matrix::Matrix(const int _rows,
               const int _cols) : rows(_rows),
                                  cols(_cols),
                                  data(_rows,
                                       std::vector<double>(_cols, 0.0)) {}

Matrix::Matrix(const int                              _rows,
               const int                              _cols,
               const std::vector<std::vector<double>> _data) : rows(_rows),
                                                               cols(_cols),
                                                               data(_data) {}

Matrix::Matrix(const Matrix& _matrix) : rows(_matrix.rows),
                                        cols(_matrix.cols),
                                        data(_matrix.data) {}


Matrix& Matrix::operator=(const Matrix& _matrix) {
    rows = _matrix.getRows();
    cols = _matrix.getCols();
    data = _matrix.getData();
    return *this;
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getCols() const {
    return cols;
}

std::vector<std::vector<double>> Matrix::getData() const {
    return data;
}

void Matrix::setRows(const int _rows) {
    rows = _rows;
    data.resize(rows);
}

void Matrix::setCols(const int _cols) {
    cols = _cols;
    for (int idx{0}; idx < rows; ++idx) {
        data[idx].resize(cols);
    }
}

void Matrix::setData(std::vector<std::vector<double>> _data) {
    data = _data;
    rows = data.size();
    cols = data[0U].size();
}

Matrix Matrix::operator+(const Matrix& _matrix) const {
    Matrix result(rows, cols);

    for (int idx{0}; idx < getRows(); ++idx) {
        for (int jdx{0}; jdx < getCols(); ++jdx) {
            result.data[idx][jdx] = data[idx][jdx] + _matrix.data[idx][jdx];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& _matrix) const {
    Matrix result(rows, cols);

    for (int idx{0}; idx < getRows(); ++idx) {
        for (int jdx{0}; jdx < getCols(); ++jdx) {
            result.data[idx][jdx] = data[idx][jdx] - _matrix.data[idx][jdx];
        }
    }
    return result;
}

Matrix Matrix::operator*(const double& _scalar) const {
    Matrix result(rows, cols, data);

    for (int idx{0}; idx < rows; ++idx) {
        for (int jdx{0}; jdx < cols; ++jdx) {
            result.data[idx][jdx] *= _scalar;
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& _matrix) const {
    Matrix res(rows, _matrix.cols);

    for (int idx{0}; idx < rows; ++idx) {
        for (int jdx{0}; jdx < _matrix.cols; ++jdx) {
            for (int kdx{0}; kdx < cols; ++kdx) {
                res.data[idx][jdx] += data[idx][kdx] * _matrix.data[kdx][jdx];
            }
        }
    }
    return res;
}

bool Matrix::operator== (const Matrix& _matrix) const {
    if (rows != _matrix.rows ||
        cols != _matrix.cols) {
        return false;
    }

    for (int idx{0}; idx < getRows(); ++idx) {
        for (int jdx{0}; jdx < getCols(); ++jdx) {
            if (data[idx][jdx] != _matrix.data[idx][jdx]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!= (const Matrix& _matrix) const {
    return !(*this == _matrix);
}

double Matrix::determinant() {
    double sum12;
    double sum22;
    sum12 = 0.0;
    sum22 = 0.0;
    for (int idx{0}; idx < rows; idx++) {
        double sum11 = 1.0;
        double sum21 = 1.0;
        int l = 2 * rows - 1 - idx;
        for (int jdx{0}; jdx < rows; jdx++) {
            sum21 *= data[jdx][l-- % rows];
            sum11 *= data[jdx][(jdx + idx) % (rows)];
        }
        sum22 += sum21;
        sum12 += sum11;
    }
    return sum12 - sum22;
}

Matrix Matrix::transpose() {
    Matrix result(rows, cols, data);

    for (int idx{0}; idx < getRows()-1; ++idx) {
        for (int jdx{idx + 1}; jdx < getCols(); ++jdx) {
            std::swap(result.data[jdx][idx], result.data[idx][jdx]);
        }
    }
    return result;
}

Matrix Matrix::takeInverseMatrix() {
    if (this->determinant() == 0) {
        throw "Determinant are equal zero";
    }

    int size{rows};

    Matrix A(size, size, data);
    Matrix A0(size, size, data);
    Matrix E2(size, size);
    for (int idx{0}; idx < size; idx++) {
        E2.data[idx][idx] = 2;
    }

    double N1;
    double Ninf;
    N1   = 0.0;
    Ninf = 0.0;
    for (int row{0}; row < size; ++row) {
        double colsum;
        double rowsum;
        colsum = 0.0;
        rowsum = 0.0;
        for (int col{0}; col < size; ++col) {
            rowsum += fabs(A0.data[row][col]);
            colsum += fabs(A0.data[col][row]);
        }
        N1 = std::max(colsum, N1);
        Ninf = std::max(rowsum, Ninf);
    }

    A0 = A0.transpose();
    A0 = A0 * (1 / (N1 * Ninf));

    Matrix inv{A0};
    while (fabs((A * inv).determinant() - 1) >= 0.001) {
        Matrix prev{inv};
        inv = A * prev;
        inv = inv * -1;
        inv = inv + E2;
        inv = prev * inv;
    }

    return inv;
}
