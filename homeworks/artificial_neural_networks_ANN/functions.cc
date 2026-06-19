#include "functions.h"

#include <cmath>

double targetFunction(double x)
{
    return std::cos(5*x-1)*std::exp(-x*x);
}

double targetDerivative(double x)
{
    return std::exp(-x*x) *
           (-5*std::sin(5*x-1) - 2*x*std::cos(5*x-1));
}

double targetSecondDerivative(double x)
{
    double e = std::exp(-x*x);
    double c = std::cos(5*x-1);
    double s = std::sin(5*x-1);

    return e*((4*x*x-27)*c + 20*x*s);
}