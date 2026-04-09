#include "integrator.h"
#include <cmath>

double integrate(
    const std::function<double(double)>& f,
    double a,
    double b,
    double acc,
    double eps,
    double f2,
    double f3
) {
    double h = b - a;

    if (std::isnan(f2)) {
        f2 = f(a + 2*h/6);
        f3 = f(a + 4*h/6);
    }

    double f1 = f(a + h/6);
    double f4 = f(a + 5*h/6);

    // higher-order rule
    double Q = (2*f1 + f2 + f3 + 2*f4)/6 * (b - a);

    // lower-order rule
    double q = (f1 + f2 + f3 + f4)/4 * (b - a);

    double err = std::abs(Q - q);
    double tol = acc + eps * std::abs(Q);

    if (std::abs(b - a) < 1e-15) return Q;
    if (err < tol) {
        return Q;
    } else {
        double mid = (a + b)/2;
        return integrate(f, a, mid, acc/std::sqrt(2), eps, f1, f2) +
               integrate(f, mid, b, acc/std::sqrt(2), eps, f3, f4);
    }
}

double integrate_cc(
    const std::function<double(double)>& f,
    double a,
    double b,
    double acc,
    double eps
) {
    auto g = [&](double theta) {
        double x = (a + b)/2 + (b - a)/2 * std::cos(theta);
        double dx = (b - a)/2 * std::sin(theta);
        return f(x) * dx;
    };

    return integrate(g, 1e-12, M_PI - 1e-12, acc, eps);
}

double integrate_inf(
    const std::function<double(double)>& f,
    double a,
    double acc,
    double eps
) {
    auto g = [&](double t) {
        if (t >= 1.0) t = 1 - 1e-12;
        double x = a + t/(1 - t);
        double dx = 1/((1 - t)*(1 - t));
        return f(x) * dx;
    };

    return integrate(g, 0, 1, acc, eps);
}

std::pair<double,double> integrate_err(
    const std::function<double(double)>& f,
    double a,
    double b,
    double acc,
    double eps,
    double f2,
    double f3
) {
    double h = b - a;

    if (std::isnan(f2)) {
        f2 = f(a + 2*h/6);
        f3 = f(a + 4*h/6);
    }

    double f1 = f(a + h/6);
    double f4 = f(a + 5*h/6);

    double Q = (2*f1 + f2 + f3 + 2*f4)/6 * (b - a);
    double q = (f1 + f2 + f3 + f4)/4 * (b - a);

    double err = std::abs(Q - q);
    double tol = acc + eps * std::abs(Q);

    if (err < tol) {
        return {Q, err};
    } else {
        double mid = (a + b)/2;

        auto left  = integrate_err(f, a, mid, acc/std::sqrt(2), eps, f1, f2);
        auto right = integrate_err(f, mid, b, acc/std::sqrt(2), eps, f3, f4);

        double result = left.first + right.first;
        double error  = std::sqrt(left.second*left.second +
                                  right.second*right.second);

        return {result, error};
    }
}