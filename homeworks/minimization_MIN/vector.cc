#include "vector.h"

Vector::Vector(){}

Vector::Vector(int n)
    : data(n, 0.0)
{
}

int Vector::size() const{
    return data.size();
}

double& Vector::operator[](int i){
    return data[i];
}

double Vector::operator[](int i) const{
    return data[i];
}

Vector Vector::operator+(const Vector& other) const{
    Vector result(size());
    for(int i=0;i<size();i++)
        result[i]=data[i]+other[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const{
    Vector result(size());
    for(int i=0;i<size();i++)
        result[i]=data[i]-other[i];
    return result;
}

Vector Vector::operator*(double scalar) const{
    Vector result(size());
    for(int i=0;i<size();i++)
        result[i]=data[i]*scalar;
    return result;
}

double Vector::norm() const{
    double sum=0;
    for(double x:data)
        sum+=x*x;
    return std::sqrt(sum);
}

std::ostream& operator<<(std::ostream& os,const Vector& v){
    for(int i=0;i<v.size();i++)
        os<<v[i]<<" ";
    return os;
}