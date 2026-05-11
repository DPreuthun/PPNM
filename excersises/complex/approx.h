#ifndef APPROX_H
#define APPROX_H

#include <complex>

bool approx(double a,
            double b,
            double acc = 1e-9,
            double eps = 1e-9);

bool approx(std::complex<double> a,
            std::complex<double> b,
            double acc = 1e-9,
            double eps = 1e-9);

#endif