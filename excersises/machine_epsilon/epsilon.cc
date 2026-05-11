#include "epsilon.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

void machineEpsilon() {
    std::cout << "===== MACHINE EPSILON =====\n";

    float f = 1.0f;
    while ((float)(1.0f + f) != 1.0f) {
        f /= 2.0f;
    }
    f *= 2.0f;

    double d = 1.0;
    while ((double)(1.0 + d) != 1.0) {
        d /= 2.0;
    }
    d *= 2.0;

    long double ld = 1.0L;
    while ((long double)(1.0L + ld) != 1.0L) {
        ld /= 2.0L;
    }
    ld *= 2.0L;

    std::cout << std::setprecision(20);

    std::cout << "Calculated float epsilon      = " << f << "\n";
    std::cout << "Calculated double epsilon     = " << d << "\n";
    std::cout << "Calculated long double eps    = " << ld << "\n\n";

    std::cout << "numeric_limits<float>::epsilon()      = "
              << std::numeric_limits<float>::epsilon() << "\n";

    std::cout << "numeric_limits<double>::epsilon()     = "
              << std::numeric_limits<double>::epsilon() << "\n";

    std::cout << "numeric_limits<long double>::epsilon() = "
              << std::numeric_limits<long double>::epsilon() << "\n\n";

    std::cout << "Expected double epsilon ≈ 2^-52 = "
              << std::pow(2.0, -52) << "\n";

    std::cout << "Expected float epsilon  ≈ 2^-23 = "
              << std::pow(2.0, -23) << "\n\n";
}

void nonCommutativity() {
    std::cout << "===== NON-COMMUTATIVITY OF ADDITION =====\n";

    double epsilon = std::pow(2.0, -52);
    double tiny = epsilon / 2.0;

    double a = 1 + tiny + tiny;
    double b = tiny + tiny + 1;

    std::cout << std::fixed << std::setprecision(17);

    std::cout << "tiny = " << tiny << "\n\n";

    std::cout << "a = 1 + tiny + tiny = " << a << "\n";
    std::cout << "b = tiny + tiny + 1 = " << b << "\n\n";

    std::cout << "a == b ? " << (a == b ? "true" : "false") << "\n";
    std::cout << "a > 1  ? " << (a > 1 ? "true" : "false") << "\n";
    std::cout << "b > 1  ? " << (b > 1 ? "true" : "false") << "\n\n";
}