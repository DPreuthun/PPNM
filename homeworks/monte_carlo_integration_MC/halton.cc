#include "halton.h"

Halton::Halton(int dim_) : dim(dim_), count(0) {
    int primes[] = {2,3,5,7,11,13,17,19};
    bases.assign(primes, primes + dim);
}

double Halton::van_der_corput(int n, int base) const {
    double vdc = 0.0;
    double denom = 1.0;

    while (n > 0) {
        denom *= base;
        vdc += (n % base) / denom;
        n /= base;
    }
    return vdc;
}

std::vector<double> Halton::next() {
    count++;
    std::vector<double> x(dim);

    for (int i = 0; i < dim; i++) {
        x[i] = van_der_corput(count, bases[i]);
    }
    return x;
}