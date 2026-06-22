#include "matrix.h"

#include <cmath>
#include <stdexcept>

//------------------------------------------------------------
// Matrix class
//------------------------------------------------------------

Matrix::Matrix(int r, int c)
    : rows(r), cols(c), data(r, std::vector<double>(c, 0.0))
{}

int Matrix::numRows() const {
    return rows;
}

int Matrix::numCols() const {
    return cols;
}

double& Matrix::operator()(int i, int j) {
    return data[i][j];
}

double Matrix::operator()(int i, int j) const {
    return data[i][j];
}

Vector Matrix::operator*(const Vector& v) const {

    if ((int)v.size() != cols)
        throw std::runtime_error("Matrix-vector size mismatch.");

    Vector result(rows, 0.0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i] += data[i][j] * v[j];
        }
    }

    return result;
}

Matrix Matrix::identity(int n) {

    Matrix I(n, n);

    for (int i = 0; i < n; i++)
        I(i, i) = 1.0;

    return I;
}

//------------------------------------------------------------
// Vector utilities
//------------------------------------------------------------

double dot(const Vector& a, const Vector& b) {

    if (a.size() != b.size())
        throw std::runtime_error("Dot product: vectors have different sizes.");

    double sum = 0.0;

    for (size_t i = 0; i < a.size(); i++)
        sum += a[i] * b[i];

    return sum;
}

double norm(const Vector& v) {
    return std::sqrt(dot(v, v));
}

void normalize(Vector& v) {

    double n = norm(v);

    if (n == 0.0)
        throw std::runtime_error("Cannot normalize zero vector.");

    for (double& x : v)
        x /= n;
}

#include <random>

Matrix testMatrix(int n)
{
    Matrix H(n,n);

    for(int i=0;i<n;i++)
    {
        H(i,i)=2.0;

        if(i>0)
            H(i,i-1)=-1.0;

        if(i<n-1)
            H(i,i+1)=-1.0;
    }

    return H;
}