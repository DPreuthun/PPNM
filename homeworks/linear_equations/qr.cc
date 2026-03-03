#include "qr.h"
#include <iomanip>

namespace pp {

// Perform modified Gram-Schmidt QR decomposition of A
QR::QR(const matrix& A)
    : Q(A), R(A.col_count(), A.col_count())
{
    int m = A.row_count();
    int n = A.col_count();

    for (int i = 0; i < n; i++) {

        double norm = Q.column(i).norm();
        R(i,i) = norm;

        for (int k = 0; k < m; k++)
            Q(k,i) /= norm;

        for (int j = i+1; j < n; j++) {

            double dot = 0.0;

            for (int k = 0; k < m; k++)
                dot += Q(k,i) * Q(k,j);

            R(i,j) = dot;

            for (int k = 0; k < m; k++)
                Q(k,j) -= Q(k,i) * dot;
        }
    }
}


// Solve Ax = b via Rx = Q^T b
vector QR::solve(const vector& b) const {

    int m = Q.row_count();
    int n = R.row_count();

    vector y(n);

    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int k = 0; k < m; k++)
            sum += Q(k,i) * b[k];
        y[i] = sum;
    }

    vector x(n);

    for (int i = n-1; i >= 0; i--) {
        double sum = y[i];
        for (int j = i+1; j < n; j++)
            sum -= R(i,j) * x[j];
        x[i] = sum / R(i,i);
    }

    return x;
}


// Return determinant as product of diagonal elements of R
double QR::det() const {

    double determinant = 1.0;

    for (int i = 0; i < R.row_count(); i++)
        determinant *= R(i,i);

    return determinant;
}


// Compute inverse by solving Ax = e_i
matrix QR::inverse() const {

    int n = R.row_count();
    matrix inv(n, n);

    for (int i = 0; i < n; i++) {

        vector e(n);
        e[i] = 1.0;

        vector x = solve(e);

        inv.set_column(i, x);
    }

    return inv;
}

} // namespace pp