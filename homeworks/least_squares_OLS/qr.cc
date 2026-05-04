#include "qr.h"
#include <cmath>

void qr_decomposition(const Matrix& A, Matrix& Q, Matrix& R) {
    int m = A.rows;
    int n = A.cols;

    Q = Matrix(m, n);
    R = Matrix(n, n);

    for (int j = 0; j < n; j++) {
        std::vector<double> v(m);
        for (int i = 0; i < m; i++)
            v[i] = A[i][j];

        for (int k = 0; k < j; k++) {
            double dot = 0;
            for (int i = 0; i < m; i++)
                dot += Q[i][k] * A[i][j];

            R[k][j] = dot;

            for (int i = 0; i < m; i++)
                v[i] -= dot * Q[i][k];
        }

        double norm = 0;
        for (int i = 0; i < m; i++)
            norm += v[i] * v[i];
        norm = std::sqrt(norm);

        R[j][j] = norm;

        for (int i = 0; i < m; i++)
            Q[i][j] = v[i] / norm;
    }
}

std::vector<double> back_substitution(const Matrix& R, const std::vector<double>& b) {
    int n = R.rows;
    std::vector<double> x(n);

    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++)
            x[i] -= R[i][j] * x[j];
        x[i] /= R[i][i];
    }

    return x;
}