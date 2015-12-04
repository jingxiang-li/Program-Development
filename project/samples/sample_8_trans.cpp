#include <iostream>
#include "Matrix.h"
#include <math.h>
using namespace std;
int main ( ) {
    matrix m ( matrix::readMatrix ("../samples/sample_8.data") ) ;
    cout << m ;
}

