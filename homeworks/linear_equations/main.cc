#include "vecmatrix.h"
#include "qr.h"
#include <iostream>
#include <iomanip>
#include <random>

int main() {

    // A2
    std::cout << std::fixed << std::setprecision(6);
    
    std::cout << "A2:" << "\n";

    // Generate random tall matrix A2
    pp::matrix A2 = pp::random_int_matrix(4,3,1,10);

    std::cout << "A2 = " << "\n" << A2 << "\n";

    // Factorise into QR and check that R is upper triangular
    pp::QR qr2(A2);

    pp::matrix Q2 = qr2.getQ();
    pp::matrix R2 = qr2.getR();

    std::cout << "R = " << "\n" << R2 << "\n";

    // Check Q^T * Q = I
    pp::matrix Q2_trans = Q2.transpose();

    std::cout << "Q^T * Q = " << "\n" << Q2_trans * Q2 << "\n";

    // Check that QR = A
    std::cout << "Q * R = " << "\n" << Q2 * R2 << "\n";

    // A3
    std::cout << "A3:" << "\n";

    // Generate a random square matrix A3
    pp::matrix A3 = pp::random_int_matrix(3,3,1,10);

    std::cout << "A3 = " << "\n" << A3 << "\n";

    // Generate a random vector b
    pp::vector b = pp::random_int_vector(3,1,10);

    std::cout << "b = " << b << "\n";

    // Factorise A into QR and solve QRx = b
    pp::QR qr3(A3);

    pp::vector x = qr3.solve(b);

    std::cout << "x = " << x << "\n";

    // Check Ax = b
    std::cout << "A * x = " << A3 * x << "\n";

    // A4
    std::cout << "A4:" << "\n";

    // Check that det(R) = det(A)

    pp::matrix Q3 = qr3.getQ();
    pp::matrix R3 = qr3.getR();

    double det_R3 = R3.det();
    double det_A3 = A3.det();

    std::cout << "R = " << "\n" << A3 << "\n";
    std::cout << "R = " << "\n" << R3 << "\n";

    std::cout << "det(A) = " << det_A3 << "\n";
    std::cout << "det(R) = " << det_R3 << "\n";
    
    // B1 
    std::cout << "B1:" << "\n";

    // Generate square matrix A (reusing the one from before)
    std::cout << "A = " << "\n" << A3 << "\n";

    // Factorize A into QR
    // Calculate inverse of B
    pp::matrix A3_inv = qr3.inverse();

    std::cout << "B = A^-1 = " << "\n" << A3_inv << "\n";

    // Check that A^-1 * B = I
    std::cout << "A * B = " << "\n" << A3 * A3_inv << "\n";

    return 0;
}