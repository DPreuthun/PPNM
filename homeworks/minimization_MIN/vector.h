#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <cmath>
#include <iostream>

class Vector {
private:
    std::vector<double> data;

public:
    Vector();
    Vector(int n);

    int size() const;

    double& operator[](int i);
    double operator[](int i) const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;

    double norm() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};

#endif