#include "./Matrix.h"
#include <fstream>
#include <iostream>

matrix::matrix(int row, int col) : rows(row), cols(col) {
    data = new float *[rows];
    for (int i = 0; i != rows; i++) {
        data[i] = new float[cols];
        for (int j = 0; j != cols; j++) data[i][j] = 0;
    }
}

matrix::matrix(const matrix &m) : rows(m.rows), cols(m.cols) {
    data = new float *[rows];
    for (int i = 0; i != rows; i++) {
        data[i] = new float[cols];
        for (int j = 0; j != cols; j++) {
            data[i][j] = m[i][j];
        }
    }
}

matrix::~matrix() {
    for (int i = 0; i != rows; i++) {
        delete[] data[i];
    }
    delete[] data;
}

int matrix::numRows() const { return rows; }

int matrix::numCols() const { return cols; }

float *matrix::operator[](int row) { return data[row]; }

const float *matrix::operator[](int row) const { return data[row]; }

/* DEPRECATED, USE [][]
float *matrix::access(int row, int col) const {
    return data[row] + col;
}
 */

std::ostream &operator<<(std::ostream &os, const matrix &m) {
    os << m.numRows() << " " << m.numCols() << std::endl;
    for (int i = 0; i != m.numRows(); i++) {
        for (int j = 0; j != m.numCols(); j++) {
            os << m[i][j] << "  ";
        }
        os << std::endl;
    }
    return os;
}

matrix operator*(const matrix &left, const matrix &right) {
    if (left.numCols() != right.numRows()) {
        std::cerr << "ERROR, two matrices cannot be multiplied with dimensions "
                  << left.numRows() << "x" << left.numCols() << " and "
                  << right.numRows() << "x" << right.numCols() << std::endl;
        exit(1);
    }

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

matrix matrixRead(const char *filename) {
    std::ifstream is(filename, std::ifstream::in);

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

matrix matrixRead(std::string &filename) {
    return matrixRead(filename.c_str());
}

int numRows(matrix &m) { return m.numRows(); }

int numCols(matrix &m) { return m.numCols(); }
