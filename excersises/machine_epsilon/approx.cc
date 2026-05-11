#include "approx.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

bool approx(double a, double b, double acc, double eps) {
    double diff = std::abs(a - b);

    // Absolute tolerance
    if (diff <= acc) {
        return true;
    }

    // Relative tolerance
    double max_ab = std::max(std::abs(a), std::abs(b));

    return diff <= eps * max_ab;
}

void compareDoubles() {
    std::cout << "===== COMPARING DOUBLES =====\n";

    double d1 = 0.1 + 0.1 + 0.1 + 0.1
              + 0.1 + 0.1 + 0.1 + 0.1;

    double d2 = 8 * 0.1;

    std::cout << std::fixed << std::setprecision(17);

    std::cout << "d1 = " << d1 << "\n";
    std::cout << "d2 = " << d2 << "\n\n";

    std::cout << "d1 == d2 ? "
              << (d1 == d2 ? "true" : "false") << "\n";

    std::cout << "approx(d1, d2) ? "
              << (approx(d1, d2) ? "true" : "false") << "\n\n";
}