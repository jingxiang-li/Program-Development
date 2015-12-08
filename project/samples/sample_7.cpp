#include <cmath>
#include <iostream>
#include "Matrix.h"

int main () {
matrix m(10, 10);
for (int i = 0; i != m.numRows(); i++)
for (int j = 0; j != m.numCols(); j++) {
m[i][j] = i * j;
}
int i;
int j;
for (i = 0; i <= 9; i++) {
for (j = 0; j <= 9; j++) {
std::cout << m[i][j];
std::cout << "  ";
}
std::cout << "\n";
}
for (i = 0; i <= 9; i++) {
for (j = 0; j <= 9; j++) {
m[i][j] = m[i][j] + 100;
}
}
for (i = 0; i <= 9; i++) {
for (j = 0; j <= 9; j++) {
std::cout << m[i][j];
std::cout << "  ";
}
std::cout << "\n";
}
}
