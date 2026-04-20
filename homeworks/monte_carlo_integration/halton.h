#ifndef HALTON_H
#define HALTON_H

#include <vector>

class Halton {
private:
    int dim;
    int count;
    std::vector<int> bases;

    double van_der_corput(int n, int base) const;

public:
    Halton(int dim_);

    std::vector<double> next();
};

#endif