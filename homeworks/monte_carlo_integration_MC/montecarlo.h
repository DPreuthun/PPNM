#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <vector>
#include <functional>

struct MCResult {
    double value;
    double error;
};

MCResult plain_mc(
    const std::function<double(const std::vector<double>&)>& f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N,
    std::function<double()> rng
);

MCResult qmc(
    const std::function<double(const std::vector<double>&)>& f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N
);

MCResult stratified_mc(
    const std::function<double(const std::vector<double>&)>& f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N,
    std::function<double()> rng,
    int Nmin = 1000
);

#endif