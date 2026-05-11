#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <string>

class vec {

public:

    double x;
    double y;
    double z;

    // Constructors
    vec();
    vec(double x, double y, double z);

    // Rule of Five
    vec(const vec& other);
    vec(vec&& other);

    vec& operator=(const vec& other);
    vec& operator=(vec&& other);

    ~vec();

    // Operators
    vec& operator+=(const vec& other);
    vec& operator-=(const vec& other);

    vec operator-() const;

    // Methods
    void print(std::string s = "") const;

    double norm() const;

    double dot(const vec& other) const;

    vec cross(const vec& other) const;
};

// Non-member operators
vec operator+(vec a, const vec& b);

vec operator-(vec a, const vec& b);

vec operator*(double c, vec v);

vec operator*(vec v, double c);

std::ostream& operator<<(std::ostream& os,
                         const vec& v);

// approx
bool approx(double a,
            double b,
            double acc = 1e-9,
            double eps = 1e-9);

bool approx(const vec& a,
            const vec& b,
            double acc = 1e-9,
            double eps = 1e-9);

#endif