#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <functional>
#include <cmath>
#include <utility>

std::pair<double,double> integrate_err(
    const std::function<double(double)>& f,
    double a,
    double b,
    double acc,
    double eps,
    double f2 = NAN,
    double f3 = NAN
);

double integrate(
    const std::function<double(double)>& f,
    double a,
    double b,
    double acc,
    double eps,
    double f2 = NAN,
    double f3 = NAN
);

double integrate_cc(
    const std::function<double(double)>& f,
    double a,
    double b,
    double acc,
    double eps
);

double integrate_inf(
    const std::function<double(double)>& f,
    double a,
    double acc,
    double eps
);

#endif