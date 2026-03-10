#include "vecmatrix.h"
#include <iomanip>
#include <random>
#include <stdexcept>

namespace pp {

/* ================= VECTOR ================= */

vector::vector(int n) : data(n, 0.0) {}

vector::vector(int n, double value) : data(n, value) {}

int vector::size() const {
    return data.size();
}

double& vector::operator[](int i) {
    return data[i];
}

double vector::operator[](int i) const {
    return data[i];
}

double vector::dot(const vector& other) const {
    if (size() != other.size())
        throw std::runtime_error("Dot product: size mismatch");

    double sum = 0.0;
    for (int i = 0; i < size(); i++)
        sum += data[i] * other[i];

    return sum;
}

double vector::norm() const {
    return std::sqrt(this->dot(*this));
}

void vector::print() const {
    for (int i = 0; i < size(); i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

vector random_int_vector(int n, int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());   // fixed seed (reproducible)
    std::uniform_int_distribution<int> dist(min, max);

    vector v(n);

    for (int i = 0; i < n; i++)
        v[i] = dist(gen);

    return v;
}

/* ================= MATRIX ================= */

matrix::matrix(int r, int c)
    : rows(r), cols(c), data(r * c, 0.0) {}

matrix::matrix(int r, int c, double value)
    : rows(r), cols(c), data(r * c, value) {}

int matrix::row_count() const {
    return rows;
}

int matrix::col_count() const {
    return cols;
}

void pp::matrix::make_symmetric(){

    int n = row_count();

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){

            double val = 0.5*( (*this)(i,j) + (*this)(j,i) );

            (*this)(i,j)=val;
            (*this)(j,i)=val;
        }
    }
}

matrix random_int_matrix(int m, int n, int min, int max) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    pp::matrix A(m,n);

    for (int r = 0; r < m; r++)
        for (int c = 0; c < n; c++)
            A(r,c) = dist(gen);

    return A;
}

double matrix::det() const {

    if (row_count() != col_count())
        throw std::runtime_error("Determinant requires square matrix");

    int n = row_count();

    matrix A = *this;   // make copy
    double determinant = 1.0;

    for (int i = 0; i < n; i++) {

        // Pivot
        if (A(i,i) == 0.0)
            return 0.0;

        determinant *= A(i,i);

        for (int j = i+1; j < n; j++) {

            double factor = A(j,i) / A(i,i);

            for (int k = i; k < n; k++)
                A(j,k) -= factor * A(i,k);
        }
    }

    return determinant;
}

double& matrix::operator()(int i, int j) {

    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }

    return data[i * cols + j];
}

double matrix::operator()(int i, int j) const {

    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }

    return data[i * cols + j];
}

vector matrix::column(int j) const {
    vector v(rows);
    for (int i = 0; i < rows; i++)
        v[i] = (*this)(i, j);
    return v;
}

void matrix::set_column(int j, const vector& v) {
    if (v.size() != rows)
        throw std::runtime_error("Column size mismatch");

    for (int i = 0; i < rows; i++)
        (*this)(i, j) = v[i];
}

matrix matrix::transpose() const {
    matrix T(cols, rows);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            T(j, i) = (*this)(i, j);

    return T;
}

vector matrix::operator*(const vector& v) const {
    if (cols != v.size())
        throw std::runtime_error("Matrix-vector size mismatch");

    vector result(rows);

    for (int i = 0; i < rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < cols; j++)
            sum += (*this)(i, j) * v[j];
        result[i] = sum;
    }

    return result;
}

matrix matrix::operator*(const matrix& B) const {
    if (cols != B.rows)
        throw std::runtime_error("Matrix-matrix size mismatch");

    matrix C(rows, B.cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < B.cols; j++)
            for (int k = 0; k < cols; k++)
                C(i, j) += (*this)(i, k) * B(k, j);

    return C;
}

matrix matrix::identity(int n) {
    matrix I(n, n);
    for (int i = 0; i < n; i++)
        I(i, i) = 1.0;
    return I;
}

void matrix::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            std::cout << (*this)(i, j) << " ";
        std::cout << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const vector& v) {
    for (int i = 0; i < v.size(); i++)
        os << v[i] << " ";
    return os;
}

std::ostream& operator<<(std::ostream& os, const matrix& M) {

    for (int i = 0; i < M.row_count(); i++) {
        for (int j = 0; j < M.col_count(); j++) {
            os << std::setw(12) << M(i,j) << " ";
        }
        os << "\n";
    }
    return os;
}

} // namespace pp