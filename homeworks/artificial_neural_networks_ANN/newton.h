#ifndef NEWTON_H
#define NEWTON_H

#include "vector.h"
#include "matrix.h"
#include <functional>

Vector gradient(std::function<double(const Vector&)> f, Vector x);

Matrix hessian(std::function<double(const Vector&)> f, Vector x);

Vector newton(std::function<double(const Vector&)> f,
              Vector x,
              double acc,
              int& steps);

Vector gradientCentral(std::function<double(const Vector&)> f, Vector x);

Matrix hessianCentral(std::function<double(const Vector&)> f, Vector x);

Vector newtonCentral(std::function<double(const Vector&)> f,
                     Vector x,
                     double acc,
                     int& steps);

#endif