#ifndef HIGGS_H
#define HIGGS_H
#include <string>

#include <vector>
#include "vector.h"

class HiggsFit {
private:
    std::vector<double> energy;
    std::vector<double> signal;
    std::vector<double> error;

public:

    void readData();

    double breitWigner(double E,
                       double m,
                       double gamma,
                       double A) const;

    double deviation(const Vector& p) const;

    void writeData(const std::string& filename) const;

    void writeFit(const std::string& filename,
                const Vector& parameters) const;

    int size() const;
};

#endif