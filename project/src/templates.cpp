/* from github as of 20 September 2015
 Jingxiang Li
 Tanoja Sunkam

 Csci3081 Lab 4.
 This file has been taken from: http://www.cplusplus.com/doc/tutorial/templates/
 It is largely a vehicle for experimenting with team work using git.
 However, templates are an extremely powerful component of c++, albeit
 complicated.
 Spending time to learn the basics of templating may save you time on your
 project.
 */
#include <iostream>
using namespace std;

template <class T, int N>
class mysequence {
    T memblock [N];
public:
    void setmember (int x, T value);
    T getmember (int x);
};

template <class T, int N>
void mysequence<T,N>::setmember (int x, T value) {
    memblock[x]=value;
}

template <class T, int N>
T mysequence<T,N>::getmember (int x) {
    return memblock[x];
}

int main () {
    mysequence <int,5> myints;
    mysequence <double,5> myfloats;
    myints.setmember (0,100);
    myfloats.setmember (3,3.1416);
    cout << myints.getmember(0) << '\n';
    cout << myfloats.getmember(3) << '\n';

    cout << "Jingxiang Li" << '\n';
    cout << "Tanoja Sunkam" << '\n';
    return 0;
}
