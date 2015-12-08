#include <cmath>
#include <iostream>
#include "Matrix.h"

int main () {
int x;
x = 0;
int y;
for (y = 1; y <= 10; y++) {
std::cout << y;
std::cout << "\n";
x = x + y;
}
std::cout << x;
std::cout << "\n";
}
