#pragma once
#include "linalg.h"
#include <functional>

Vec newton(std::function<Vec(const Vec&)> f,
           Vec x,
           double acc = 1e-6,
           double alpha_min = 1e-3,
           int max_iter = 100);