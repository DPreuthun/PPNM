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

    std::cout << "----------A1----------" << "\n";

    std::cout << "A = " << "\n" << A1 << "\n";

    pp::matrix AJ = A1;

    pp::timesJ(AJ, 0, 1, M_PI/4.0);

    std::cout << "A * J = " << "\n" << AJ << "\n";

    // A2
    pp::matrix A2 = pp::random_int_matrix(4,4,1,10);

    std::cout << "----------A2----------" << "\n";

    std::cout << "A = " << "\n" << A2 << "\n";

    pp::matrix JA = A2;

    pp::timesJ(JA, 0, 1, M_PI/4.0);

    std::cout << "J * A = " << "\n" << JA << "\n";

    // A3
    std::cout << "----------A3----------" << "\n";

    pp::matrix A3 = pp::random_int_matrix(4,4,1,10);

    A3.make_symmetric();

    pp::matrix A3_original = A3;

    std::cout << "A_sym = " << "\n" << A3 << "\n";

    pp::matrix V(4,4);
    
    pp::jacobi(A3,V);

    pp::matrix D = A3;

    std::cout << "D = " << "\n" << D << "\n";

    std::cout << "V = " << "\n" << V << "\n";

    std::cout << "V^T * A * V = " << "\n" << V.transpose() * A3_original * V << "\n";

    std::cout << "V * D * V^T = " << "\n" << V * D * V.transpose() << "\n";

    std::cout << "V^T * V = " << "\n" << V.transpose() * V << "\n";

    std::cout << "V * V^T = " << "\n" << V * V.transpose() << "\n";

    

    return 0;
}