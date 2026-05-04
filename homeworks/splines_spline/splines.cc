#include "splines.h"
#include <cassert>

namespace pp {

int binsearch(const vector& x, double z) {
    assert(z >= x[0] && z <= x[x.size() - 1]);

    int i = 0;
    int j = x.size() - 1;

    while (j - i > 1) {
        int mid = (i + j) / 2;
        if (z > x[mid])
            i = mid;
        else
            j = mid;
    }

    return i;
}

double linterp(const vector& x, const vector& y, double z) {
    assert(x.size() == y.size());

    int i = binsearch(x, z);

    double dx = x[i + 1] - x[i];
    assert(dx > 0);

    double dy = y[i + 1] - y[i];

    return y[i] + dy / dx * (z - x[i]);
}

double linterpInteg(const vector& x, const vector& y, double z) {
    assert(x.size() == y.size());
    assert(z >= x[0] && z <= x[x.size() - 1]);

    int i = binsearch(x, z);

    double sum = 0.0;

    // 1. Sum full intervals (trapezoids)
    for (int k = 0; k < i; k++) {
        double dx = x[k+1] - x[k];
        double area = 0.5 * (y[k] + y[k+1]) * dx;
        sum += area;
    }

    // 2. Partial interval from x[i] to z
    double dx = x[i+1] - x[i];
    double dy = y[i+1] - y[i];

    double slope = dy / dx;

    // Linear function: f(t) = y[i] + slope*(t - x[i])
    // Integral analytically:
    double dz = z - x[i];

    double partial =
        y[i] * dz +           // rectangle part
        0.5 * slope * dz*dz;  // triangle part

    sum += partial;

    return sum;
}

} // namespace pp

// ================= QUADRATIC SPLINE =================

namespace pp {

qspline::qspline(const vector& xs, const vector& ys)
    : x(xs), y(ys), b(xs.size()-1), c(xs.size()-1)
{
    int n = x.size();
    assert(n > 1);
    assert(y.size() == n);

    vector dx(n-1), p(n-1);

    // compute intervals and slopes
    for (int i = 0; i < n-1; i++) {
        dx[i] = x[i+1] - x[i];
        assert(dx[i] > 0);
        p[i] = (y[i+1] - y[i]) / dx[i];
    }

    // forward pass
    c[0] = 0;
    for (int i = 0; i < n-2; i++) {
        c[i+1] = (p[i+1] - p[i] - c[i]*dx[i]) / dx[i+1];
    }

    // backward pass
    c[n-2] /= 2;
    for (int i = n-3; i >= 0; i--) {
        c[i] = (p[i+1] - p[i] - c[i+1]*dx[i+1]) / dx[i];
    }

    // compute b coefficients
    for (int i = 0; i < n-1; i++) {
        b[i] = p[i] - c[i]*dx[i];
    }
}


double qspline::eval(double z) const {
    int i = binsearch(x, z);
    double dx = z - x[i];
    return y[i] + b[i]*dx + c[i]*dx*dx;
}


double qspline::deriv(double z) const {
    int i = binsearch(x, z);
    double dx = z - x[i];
    return b[i] + 2*c[i]*dx;
}


double qspline::integ(double z) const {
    int i = binsearch(x, z);

    double sum = 0;

    // sum full intervals
    for (int k = 0; k < i; k++) {
        double dx = x[k+1] - x[k];
        sum += y[k]*dx
             + b[k]*dx*dx/2
             + c[k]*dx*dx*dx/3;
    }

    // partial interval
    double dx = z - x[i];
    sum += y[i]*dx
         + b[i]*dx*dx/2
         + c[i]*dx*dx*dx/3;

    return sum;
}

} // namespace pp