#include "./Matrix.h"
#include <fstream>
#include <iostream>

matrix::matrix(int row, int col) : rows(row), cols(col) {
    data = new float *[rows];
    for (int i = 0; i != rows; i++) {
        data[i] = new float[cols];
    }
}

matrix::matrix(const matrix &m) {
    data = new float *[rows];
    for (int i = 0; i != rows; i++) {
        data[i] = new float[cols];
    }
    for (int i = 0; i != rows; i++)
        for (int j = 0; j != cols; j++) {
            data[i][j] = m[i][j];
        }
}

int matrix::numRows() const { return rows; }

int matrix::numCols() const { return cols; }

float *matrix::operator[](int row) { return data[row]; }

const float *matrix::operator[](int row) const { return data[row]; }

std::ostream &operator<<(std::ostream &os, const matrix &m) {
    for (int i = 0; i != m.numRows(); i++) {
        for (int j = 0; j != m.numCols(); j++) {
            os << m[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

matrix operator*(const matrix &left, const matrix &right) {
    matrix m(left.numRows(), right.numCols());
    for (int i = 0; i != m.numRows(); i++) {
        for (int j = 0; j != m.numCols(); j++) {
            for (int k = 0; k != left.numCols(); k++) {
                m[i][j] += left[i][k] * right[k][j];
            }
        }
    }
    return m;
}

matrix matrix::matrixRead(std::string filename) {
    std::ifstream is(filename.c_str(), std::ifstream::in);

    // read nrows and ncols
    int nrows, ncols;
    is >> nrows >> ncols;

    // initiate matrix
    matrix m(nrows, ncols);

    // read all values
    for (int i = 0; i != nrows; i++)
        for (int j = 0; j != ncols; j++) {
            is >> m[i][j];
        }
    return m;
}
