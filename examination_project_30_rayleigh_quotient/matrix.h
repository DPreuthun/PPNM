#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using Vector = std::vector<double>;

class Matrix {
private:
    int rows;
    int cols;
    std::vector<std::vector<double>> data;

public:
    Matrix(int r, int c);

    int numRows() const;
    int numCols() const;

    double& operator()(int i, int j);
    double operator()(int i, int j) const;

    Vector operator*(const Vector& v) const;

    static Matrix identity(int n);
};

double dot(const Vector& a, const Vector& b);

double norm(const Vector& v);

void normalize(Vector& v);

//------------------------------------------------------------
// Generate a random symmetric matrix
//------------------------------------------------------------

Matrix testMatrix(int n);

#endif