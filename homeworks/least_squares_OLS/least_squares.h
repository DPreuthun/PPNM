#ifndef LEAST_SQUARES_H
#define LEAST_SQUARES_H

#include "matrix.h"
#include <functional>

std::vector<double> least_squares_fit(
    const std::vector<std::function<double(double)>>& fs,
    const std::vector<double>& x,
    const std::vector<double>& y,
    const std::vector<double>& dy,
    Matrix* R_out = nullptr
);

std::vector<std::vector<double>> covariance_matrix(const Matrix& R);

#endif