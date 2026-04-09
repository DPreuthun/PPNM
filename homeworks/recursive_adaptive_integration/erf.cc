#include "erf.h"
#include "integrator.h"
#include <cmath>

double erf_integral(double z, double acc, double eps) {
    if (z < 0) return -erf_integral(-z, acc, eps);

    if (z <= 1) {
        auto f = [](double x) {
            return std::exp(-x*x);
        };
        return 2/std::sqrt(M_PI) * integrate(f, 0, z, acc, eps);
    } else {
        auto f = [z](double t) {
            double x = z + (1 - t)/t;
            return std::exp(-x*x)/(t*t);
        };
        return 1 - 2/std::sqrt(M_PI) * integrate(f, 0, 1, acc, eps);
    }
}