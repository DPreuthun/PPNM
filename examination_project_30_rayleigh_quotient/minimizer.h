#ifndef MINIMIZER_H
#define MINIMIZER_H

#include <functional>

//------------------------------------------------------------
// Golden section search for 1D minimization
//
// Minimizes a function f(alpha) on the interval [a,b].
//------------------------------------------------------------

double goldenSectionSearch(
    const std::function<double(double)>& f,
    double a,
    double b,
    double tolerance = 1e-6,
    int maxIterations = 200
);

#endif