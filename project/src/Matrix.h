#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <iostream>
#include <fstream>

class matrix {
public:
    matrix(int row, int col);
    matrix(const matrix &m);

    int numRows() const;
    int numCols() const;

    float *operator[](int row);

    const float *operator[](int row) const;

    friend std::ostream &operator<<(std::ostream &os, const matrix &m);

    friend matrix operator*(const matrix &left, const matrix &right);

    static matrix matrixRead(std::string filename);

private:
    // we don't implement matrix() {} ??
    matrix() {}
    int rows;
    int cols;

    /* Your implementation of "data" may vary.  There are ways in
       which data can be an array of arrays and thus simplify the
       access method, at the cost of complicating the process of
       allocating space for data.  The choice is entirely up to
       you. */
    float **data;
};

#endif  // MATRIX_H
