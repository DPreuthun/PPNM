#include "linalg.h"
#include <cmath>
#include <cassert>

double norm(const Vec& v) {
    double sum = 0;
    for (double x : v) sum += x * x;
    return std::sqrt(sum);
}

Vec solve_linear(Mat A, Vec b) {
    int n = A.size();

    // Forward elimination
    for (int i = 0; i < n; i++) {
        // Pivot
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > fabs(A[maxRow][i]))
                maxRow = k;
        }
        std::swap(A[i], A[maxRow]);
        std::swap(b[i], b[maxRow]);

        // Eliminate
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; j++)
                A[k][j] -= factor * A[i][j];
            b[k] -= factor * b[i];
        }
    }

    // Back substitution
    Vec x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }

    return x;
}