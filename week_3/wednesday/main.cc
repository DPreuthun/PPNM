#include<iostream>
#include<vector>
#include"vec.h"
#include<string>
#include<functional>
#include<complex>

using pp::vec;

int main() {
    vec<int> intvec {1, 2, 3};

    vec<double> doublevec {1.23, 2.34, 3.45};

    using cd = std::complex<double>;
    vec<cd> complexvec {cd(0,1), cd(0,2), cd(0,3)}; 

    std::cout << "Integer vector: " << intvec << "\n";
    std::cout << "Double vector:  " << doublevec << "\n";
    std::cout << "Complex vector: " << complexvec << "\n";

    vec<double> doubleAddVec = doublevec + doublevec;
    vec<int> intMultiVec = intvec * 2;
    vec<cd> complexMultiVec = complexvec * cd(0,1);

    std::cout << "Double vector + double vector: " << doubleAddVec << "\n";
    std::cout << "Integer vector * 2:            " << intMultiVec << "\n";
    std::cout << "Complex vector * i:        " << complexMultiVec << "\n";
}