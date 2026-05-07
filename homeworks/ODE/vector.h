#ifndef HAVE_VECTOR_H
#define HAVE_VECTOR_H

#include <vector>
#include <cmath>
#include <iostream>

class vector {
private:
    std::vector<double> data;

public:
    vector() {}
    vector(int n);
    vector(std::initializer_list<double> list);

    int size() const;

    double& operator[](int i);
    double operator[](int i) const;

    vector operator+(const vector& other) const;
    vector operator-(const vector& other) const;
    vector operator*(double c) const;

    double norm() const;
};

std::ostream& operator<<(std::ostream& os, const vector& v);

#endif