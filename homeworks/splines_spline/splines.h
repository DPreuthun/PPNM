#ifndef SPLINES_H
#define SPLINES_H

#include "vecmatrix.h"

namespace pp {

// Binary search: find i such that x[i] ≤ z ≤ x[i+1]
int binsearch(const vector& x, double z);

// Linear interpolation
double linterp(const vector& x, const vector& y, double z);

// Linear interpolation integration
double linterpInteg(const vector& x, const vector& y, double z);

class qspline {
private:
    vector x, y, b, c;

public:
    qspline(const vector& xs, const vector& ys);

    double eval(double z) const;
    double deriv(double z) const;
    double integ(double z) const;
};

} // namespace pp

#endif