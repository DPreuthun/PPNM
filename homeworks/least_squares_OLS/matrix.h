#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix {
public:
    int rows, cols;
    std::vector<std::vector<double>> data;

    Matrix(int r, int c);

    std::vector<double>& operator[](int i);
    const std::vector<double>& operator[](int i) const;

    static Matrix transpose(const Matrix& A);
    static Matrix multiply(const Matrix& A, const Matrix& B);
    static std::vector<double> multiply(const Matrix& A, const std::vector<double>& x);
};

#endif