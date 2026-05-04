#ifndef QR_H
#define QR_H

#include "matrix.h"

void qr_decomposition(const Matrix& A, Matrix& Q, Matrix& R);

std::vector<double> back_substitution(const Matrix& R, const std::vector<double>& b);

#endif