#include "vector.h"

vector::vector(int n) : data(n) {}

vector::vector(std::initializer_list<double> list)
    : data(list) {}

int vector::size() const {
    return data.size();
}

double& vector::operator[](int i) {
    return data[i];
}

double vector::operator[](int i) const {
    return data[i];
}

vector vector::operator+(const vector& other) const {
    vector result(size());
    for(int i=0;i<size();i++)
        result[i] = data[i] + other[i];
    return result;
}

vector vector::operator-(const vector& other) const {
    vector result(size());
    for(int i=0;i<size();i++)
        result[i] = data[i] - other[i];
    return result;
}

vector vector::operator*(double c) const {
    vector result(size());
    for(int i=0;i<size();i++)
        result[i] = data[i]*c;
    return result;
}

double vector::norm() const {
    double sum=0;
    for(double x : data)
        sum += x*x;
    return std::sqrt(sum);
}

std::ostream& operator<<(std::ostream& os, const vector& v){
    for(int i=0;i<v.size();i++)
        os << v[i] << " ";
    return os;
}