#include<limits>
#include<iostream>
#include <cmath>
#include"computeepsilon.h"
#include"actualepsilon.h"

int main() {
    computeepsilon();
    actualepsilon();

    double epsilon=std::pow(2,-52);
    double tiny=epsilon/2;
    double a=1+tiny+tiny;
    double b=tiny+tiny+1;
    std::cout << "Checking for commutation of addition:\n" << "a=1+tiny+tiny\n" << "b=tiny+tiny+1\n";
    std::cout << "a==b ? " << (a==b ? "true":"false") << "\n";
    std::cout << "a>1  ? " << (a>1  ? "true":"false") << "\n";
    std::cout << "b>1  ? " << (b>1  ? "true":"false") << "\n";
    return 0;
}

