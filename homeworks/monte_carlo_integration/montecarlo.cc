#include "montecarlo.h"
#include <cmath>

MCResult plain_mc(
    const std::function<double(const std::vector<double>&)>& f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N,
    std::function<double()> rng
) {
    int dim = a.size();

    // Volume of integration region
    double V = 1.0;
    for (int i = 0; i < dim; i++) {
        V *= (b[i] - a[i]);
    }

    double sum1 = 0.0;
    double sum2 = 0.0;

    for (int n = 0; n < N; n++) {
        std::vector<double> x(dim);

        for (int i = 0; i < dim; i++) {
            x[i] = a[i] + rng() * (b[i] - a[i]);
        }

        double fx = f(x);
        sum1 += fx;
        sum2 += fx * fx;
    }

    double mean = sum1 / N;
    double variance = sum2 / N - mean * mean;
    double sigma = std::sqrt(variance);

    MCResult result;
    result.value = mean * V;
    result.error = sigma * V / std::sqrt(N);

    return result;
}

#include "halton.h"

MCResult qmc(
    const std::function<double(const std::vector<double>&)>& f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N
) {
    int dim = a.size();

    Halton halton(dim);

    double V = 1.0;
    for (int i = 0; i < dim; i++)
        V *= (b[i] - a[i]);

    double sum = 0.0;

    for (int n = 0; n < N; n++) {
        auto u = halton.next();

        std::vector<double> x(dim);
        for (int i = 0; i < dim; i++) {
            x[i] = a[i] + u[i] * (b[i] - a[i]);
        }

        sum += f(x);
    }

    MCResult result;
    result.value = (sum / N) * V;

    // No standard variance formula → estimate later by comparison
    result.error = 0.0;

    return result;
}

MCResult stratified_mc(
    const std::function<double(const std::vector<double>&)>& f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N,
    std::function<double()> rng,
    int Nmin
) {
    int dim = a.size();

    // Base case → plain MC
    if (N < Nmin) {
        return plain_mc(f, a, b, N, rng);
    }

    // Estimate variance and find best split dimension
    int Ntest = 200;  // small sample
    std::vector<double> means(dim, 0.0);
    std::vector<double> vars(dim, 0.0);

    for (int d = 0; d < dim; d++) {
        double sum1 = 0.0, sum2 = 0.0;

        for (int i = 0; i < Ntest; i++) {
            std::vector<double> x(dim);
            for (int j = 0; j < dim; j++) {
                x[j] = a[j] + rng() * (b[j] - a[j]);
            }

            double fx = f(x);
            sum1 += fx;
            sum2 += fx * fx;
        }

        double mean = sum1 / Ntest;
        vars[d] = sum2 / Ntest - mean * mean;
    }

    // Find dimension with largest variance
    int split_dim = 0;
    for (int d = 1; d < dim; d++) {
        if (vars[d] > vars[split_dim]) split_dim = d;
    }

    // Split interval
    std::vector<double> mid = a;
    mid[split_dim] = 0.5 * (a[split_dim] + b[split_dim]);

    std::vector<double> a1 = a, b1 = b;
    std::vector<double> a2 = a, b2 = b;

    b1[split_dim] = mid[split_dim];
    a2[split_dim] = mid[split_dim];

    // Split points evenly (simple version)
    int N1 = N / 2;
    int N2 = N - N1;

    // Recursive calls
    MCResult r1 = stratified_mc(f, a1, b1, N1, rng, Nmin);
    MCResult r2 = stratified_mc(f, a2, b2, N2, rng, Nmin);

    // Combine results
    double V1 = 1.0, V2 = 1.0;
    for (int i = 0; i < dim; i++) {
        V1 *= (b1[i] - a1[i]);
        V2 *= (b2[i] - a2[i]);
    }

    MCResult res;
    res.value = r1.value + r2.value;

    // Combine errors (independent)
    res.error = std::sqrt(r1.error * r1.error + r2.error * r2.error);

    return res;
}