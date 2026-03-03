#include"actualepsilon.h"
#include<iostream>
#include<limits>

void actualepsilon(void){
    std::cout << "Actual epsilons:\n";
    std::cout << std::numeric_limits<float>::epsilon() << "\n";
    std::cout << std::numeric_limits<double>::epsilon() << "\n";
    std::cout << std::numeric_limits<long double>::epsilon() << "\n";
}