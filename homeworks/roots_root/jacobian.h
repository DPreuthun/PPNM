#pragma once
#include "linalg.h"
#include <functional>

Mat jacobian(std::function<Vec(const Vec&)> f, const Vec& x);

void jacobian_inplace(std::function<Vec(const Vec&)> f,
                      const Vec& x,
                      Mat& J);