#include "vec.h"

#include <cmath>

// Constructors
vec::vec()
    : x(0), y(0), z(0) {}

vec::vec(double x_, double y_, double z_)
    : x(x_), y(y_), z(z_) {}

// Copy constructor
vec::vec(const vec& other) = default;

// Move constructor
vec::vec(vec&& other) = default;

// Copy assignment
vec& vec::operator=(const vec& other) = default;

// Move assignment
vec& vec::operator=(vec&& other) = default;

// Destructor
vec::~vec() = default;

// +=
vec& vec::operator+=(const vec& other) {

    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

// -=
vec& vec::operator-=(const vec& other) {

    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

// Unary minus
vec vec::operator-() const {

    return vec(-x, -y, -z);
}

// Print
void vec::print(std::string s) const {

    std::cout
        << s
        << "("
        << x << ", "
        << y << ", "
        << z << ")\n";
}

double vec::norm() const {

    return std::sqrt(x*x + y*y + z*z);
}

double vec::dot(const vec& other) const {

    return
        x * other.x
      + y * other.y
      + z * other.z;
}

vec vec::cross(const vec& other) const {

    return vec(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

// +
vec operator+(vec a, const vec& b) {

    a += b;

    return a;
}

// -
vec operator-(vec a, const vec& b) {

    a -= b;

    return a;
}

// scalar multiplication
vec operator*(double c, vec v) {

    return vec(c*v.x, c*v.y, c*v.z);
}

vec operator*(vec v, double c) {

    return c * v;
}

// <<
std::ostream& operator<<(std::ostream& os,
                         const vec& v) {

    os << "("
       << v.x << ", "
       << v.y << ", "
       << v.z << ")";

    return os;
}

// approx for doubles
bool approx(double a,
            double b,
            double acc,
            double eps) {

    double diff = std::abs(a - b);

    if (diff <= acc) {
        return true;
    }

    double max_ab =
        std::max(std::abs(a), std::abs(b));

    return diff <= eps * max_ab;
}

// approx for vecs
bool approx(const vec& a,
            const vec& b,
            double acc,
            double eps) {

    if (!approx(a.x, b.x, acc, eps)) {
        return false;
    }

    if (!approx(a.y, b.y, acc, eps)) {
        return false;
    }

    if (!approx(a.z, b.z, acc, eps)) {
        return false;
    }

    return true;
}