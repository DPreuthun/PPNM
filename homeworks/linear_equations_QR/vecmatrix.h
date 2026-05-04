#ifndef CLASSES_H
#define CLASSES_H

#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>

namespace pp {

/*
========================================================
VECTOR CLASS
========================================================
*/

class vector {
private:
    std::vector<double> data;

public:
    vector(int n);
    vector(int n, double value);

    int size() const;

    double& operator[](int i);
    double operator[](int i) const;

    double dot(const vector& other) const;
    double norm() const;

    void print() const;
};


/*
========================================================
MATRIX CLASS
========================================================
*/

class matrix {
private:
    int rows;
    int cols;
    std::vector<double> data;

public:
    matrix(int r, int c);
    matrix(int r, int c, double value);

    int row_count() const;
    int col_count() const;

    double& operator()(int i, int j);
    double operator()(int i, int j) const;

    vector column(int j) const;
    void set_column(int j, const vector& v);

    matrix transpose() const;
    double det() const;

    vector operator*(const vector& v) const;
    matrix operator*(const matrix& B) const;

    static matrix identity(int n);

    void print() const;
};

// Random matrix generator
matrix random_int_matrix(int m, int n, int min, int max);

// Random vector generator
vector random_int_vector(int n, int min, int max);

// Overload output operator for vector
std::ostream& operator<<(std::ostream& os, const vector& v);

// Overload output operator for matrix
std::ostream& operator<<(std::ostream& os, const matrix& M);

} // namespace pp

#endif