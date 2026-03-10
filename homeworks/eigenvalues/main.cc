#include "vecmatrix.h"
#include "jacobi.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>

int main() {
    std::cout << std::fixed << std::setprecision(6);

    // A1
    pp::matrix A1 = pp::random_int_matrix(4,4,1,10);

    std::cout << "\n" << "----------A1----------" << "\n";

    std::cout << "A = " << "\n" << A1 << "\n";

    pp::matrix AJ = A1;

    pp::timesJ(AJ, 0, 1, M_PI/4.0);

    std::cout << "A * J = " << "\n" << AJ << "\n";

    // A2
    pp::matrix A2 = pp::random_int_matrix(4,4,1,10);

    std::cout << "\n" << "----------A2----------" << "\n";

    std::cout << "A = " << "\n" << A2 << "\n";

    pp::matrix JA = A2;

    pp::timesJ(JA, 0, 1, M_PI/4.0);

    std::cout << "J * A = " << "\n" << JA << "\n";

    // A3
    pp::matrix A3 = pp::random_int_matrix(4,4,1,10);

    pp::make_symmetric(A3);

    
    
    int rotations = pp::jacobi(A3,V);

    pp::matrix D = A;


    return 0;
}