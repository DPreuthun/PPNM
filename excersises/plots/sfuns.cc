#include "sfuns.h"

#include <cmath>
#include <vector>
#include <limits>

constexpr double PI = 3.14159265358979323846;

double erf_approx(double x) {

    if (x < 0) {
        return -erf_approx(-x);
    }

    std::vector<double> a = {
        0.254829592,
       -0.284496736,
        1.421413741,
       -1.453152027,
        1.061405429
    };

    double t = 1.0 / (1.0 + 0.3275911 * x);

    double sum =
        t * (a[0]
        + t * (a[1]
        + t * (a[2]
        + t * (a[3]
        + t * a[4]))));

    return 1 - sum * std::exp(-x * x);
}

double gamma_function(double x) {

    if (x < 0) {
        return PI /
               (std::sin(PI * x)
               * gamma_function(1 - x));
    }

    if (x < 9) {
        return gamma_function(x + 1) / x;
    }

    double lngamma =
        std::log(2 * PI) / 2
        + (x - 0.5) * std::log(x)
        - x
        + 1.0 / (12 * x)
        - 1.0 / (360 * x * x * x);

    return std::exp(lngamma);
}

double lngamma_function(double x) {

    constexpr double NaN =
        std::numeric_limits<double>::quiet_NaN();

    if (x <= 0) {
        return NaN;
    }

    if (x < 9) {
        return lngamma_function(x + 1)
             - std::log(x);
    }

    return
        x * std::log(x + 1.0 / (12 * x
        - 1.0 / (10 * x)))
        - x
        + std::log(2 * PI / x) / 2;
}