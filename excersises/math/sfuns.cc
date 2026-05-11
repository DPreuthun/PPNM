#include "sfuns.h"

#include <cmath>
#include <limits>

namespace sfuns {

constexpr double PI = 3.14159265358979323846;

double fgamma(double x) {

    if (x < 0) {
        return PI / (std::sin(PI * x) * fgamma(1 - x));
    }

    if (x < 9) {
        return fgamma(x + 1) / x;
    }

    double lng =
        x * std::log(x + 1.0 / (12 * x - 1.0 / (10 * x)))
        - x
        + std::log(2 * PI / x) / 2;

    return std::exp(lng);
}

double lngamma(double x) {

    constexpr double NaN =
        std::numeric_limits<double>::quiet_NaN();

    if (x <= 0) {
        return NaN;
    }

    if (x < 9) {
        return lngamma(x + 1) - std::log(x);
    }

    return
        x * std::log(x + 1.0 / (12 * x - 1.0 / (10 * x)))
        - x
        + std::log(2 * PI / x) / 2;
}

}