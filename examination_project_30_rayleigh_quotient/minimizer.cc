#include "minimizer.h"

#include <cmath>
#include <algorithm>

double goldenSectionSearch(
    const std::function<double(double)>& f,
    double a,
    double b,
    double tolerance,
    int maxIterations)
{
    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
    const double invPhi = 1.0 / phi;

    double c = b - (b - a) * invPhi;
    double d = a + (b - a) * invPhi;

    double fc = f(c);
    double fd = f(d);

    int iterations = 0;

    while ((b - a) > tolerance && iterations < maxIterations)
    {
        if (fc < fd)
        {
            b = d;
            d = c;
            fd = fc;

            c = b - (b - a) * invPhi;
            fc = f(c);
        }
        else
        {
            a = c;
            c = d;
            fc = fd;

            d = a + (b - a) * invPhi;
            fd = f(d);
        }

        iterations++;
    }

    return 0.5 * (a + b);
}