#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <iostream>
#include <fstream>

class matrix {
public:
    matrix(int i, int j) ;
    matrix (const matrix& m) ;

    int numRows ( ) ;
    int numCols ( ) ;

    float *access(const int i, const int j) const ;
    friend std::ostream& operator<<(std::ostream &os, matrix &m) ;

    static matrix matrixRead ( std::string filename ) ;

private:
    matrix() { }
    int rows ;
    int cols ;

    /* Your implementation of "data" may vary.  There are ways in
       which data can be an array of arrays and thus simplify the
       access method, at the cost of complicating the process of
       allocating space for data.  The choice is entirely up to
       you. */
    float *data ;
} ;

#endif // MATRIX_H
