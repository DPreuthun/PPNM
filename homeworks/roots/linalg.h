#pragma once
#include <vector>

using Vec = std::vector<double>;
using Mat = std::vector<std::vector<double>>;

Vec solve_linear(Mat A, Vec b);
double norm(const Vec& v);