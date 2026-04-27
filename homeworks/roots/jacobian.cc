#include "jacobian.h"
#include <cmath>

Mat jacobian(std::function<Vec(const Vec&)> f, const Vec& x) {
    int n = x.size();
    Vec fx = f(x);

    Mat J(n, Vec(n));
    Vec xh = x;

    for (int j = 0; j < n; j++) {
        double dx = std::max(fabs(x[j]), 1.0) * pow(2, -26);
        xh[j] += dx;

        Vec fh = f(xh);

        for (int i = 0; i < n; i++) {
            J[i][j] = (fh[i] - fx[i]) / dx;
        }

        xh[j] = x[j]; // restore
    }

    return J;
}

void jacobian_inplace(std::function<Vec(const Vec&)> f,
                      const Vec& x,
                      Mat& J) {

    int n = x.size();
    Vec fx = f(x);
    Vec xh = x;

    for (int j = 0; j < n; j++) {
        double dx = std::max(fabs(x[j]), 1.0) * pow(2, -26);
        xh[j] += dx;

        Vec fh = f(xh);

        for (int i = 0; i < n; i++) {
            J[i][j] = (fh[i] - fx[i]) / dx;
        }

        xh[j] = x[j];
    }
}