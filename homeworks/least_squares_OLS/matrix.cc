#include "matrix.h"

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<double>(c, 0.0)) {}

std::vector<double>& Matrix::operator[](int i) { return data[i]; }
const std::vector<double>& Matrix::operator[](int i) const { return data[i]; }

Matrix Matrix::transpose(const Matrix& A) {
    Matrix T(A.cols, A.rows);
    for (int i = 0; i < A.rows; i++)
        for (int j = 0; j < A.cols; j++)
            T[j][i] = A[i][j];
    return T;
}

Matrix Matrix::multiply(const Matrix& A, const Matrix& B) {
    Matrix C(A.rows, B.cols);
    for (int i = 0; i < A.rows; i++)
        for (int j = 0; j < B.cols; j++)
            for (int k = 0; k < A.cols; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

std::vector<double> Matrix::multiply(const Matrix& A, const std::vector<double>& x) {
    std::vector<double> b(A.rows, 0.0);
    for (int i = 0; i < A.rows; i++)
        for (int j = 0; j < A.cols; j++)
            b[i] += A[i][j] * x[j];
    return b;
}