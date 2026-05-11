#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>

#include "sfuns.h"

using complex = std::complex<double>;

constexpr double PI = 3.14159265358979323846;
constexpr double E  = 2.71828182845904523536;
constexpr complex I(0,1);

int main() {

    std::cout << std::fixed << std::setprecision(10);

    std::cout << "===== BASIC MATH =====\n\n";

    std::cout << "sqrt(2) = "
              << std::sqrt(2.0) << "\n";

    std::cout << "2^(1/5) = "
              << std::pow(2.0, 1.0/5.0) << "\n";

    std::cout << "e^pi = "
              << std::pow(E, PI) << "\n";

    std::cout << "pi^e = "
              << std::pow(PI, E) << "\n";

    std::cout << "sqrt(-1) = "
              << std::sqrt(complex(-1,0)) << "\n";

    std::cout << "e^i = "
              << std::exp(I) << "\n";

    std::cout << "e^(i*pi) = "
              << std::exp(I*PI) << "\n";

    std::cout << "i^i = "
              << std::pow(I,I) << "\n";

    std::cout << "log(i) = "
              << std::log(I) << "\n\n";

    std::cout << "===== GAMMA FUNCTION =====\n\n";

    for (int n = 1; n <= 10; n++) {

        std::cout
            << "Gamma(" << n << ") = "
            << sfuns::fgamma(n)
            << "\n";
    }

    std::cout << "\n";

    std::cout << "===== LOG GAMMA FUNCTION =====\n\n";

    for (int n = 1; n <= 10; n++) {

        std::cout
            << "lnGamma(" << n << ") = "
            << sfuns::lngamma(n)
            << "\n";
    }

    return 0;
}