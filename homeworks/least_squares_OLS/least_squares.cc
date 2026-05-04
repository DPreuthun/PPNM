#include "least_squares.h"
#include "qr.h"
#include <cmath>

std::vector<double> least_squares_fit(
    const std::vector<std::function<double(double)>>& fs,
    const std::vector<double>& x,
    const std::vector<double>& y,
    const std::vector<double>& dy,
    Matrix* R_out
) {
    int m = x.size();
    int n = fs.size();

    Matrix A(m, n);
    std::vector<double> b(m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = fs[j](x[i]) / dy[i];
        }
        b[i] = y[i] / dy[i];
    }

    Matrix Q(m, n), R(n, n);
    qr_decomposition(A, Q, R);

    if (R_out) {
        *R_out = R;
    }

    Matrix Qt = Matrix::transpose(Q);
    std::vector<double> Qtb = Matrix::multiply(Qt, b);

    return back_substitution(R, Qtb);
}

#include <vector>

// Invert upper triangular matrix R
Matrix invert_upper(const Matrix& R) {
    int n = R.rows;
    Matrix Rinv(n, n);

    for (int i = n - 1; i >= 0; i--) {
        Rinv[i][i] = 1.0 / R[i][i];

        for (int j = i + 1; j < n; j++) {
            double sum = 0.0;
            for (int k = i + 1; k <= j; k++) {
                sum += R[i][k] * Rinv[k][j];
            }
            Rinv[i][j] = -sum / R[i][i];
        }
    }

    return Rinv;
}

std::vector<std::vector<double>> covariance_matrix(const Matrix& R) {
    int n = R.rows;

    Matrix Rinv = invert_upper(R);
    Matrix RinvT = Matrix::transpose(Rinv);

    Matrix Cov = Matrix::multiply(Rinv, RinvT);

    std::vector<std::vector<double>> result(n, std::vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = Cov[i][j];

    return result;
}