#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>

#include "lcg.h"
#include "montecarlo.h"

int main() {
    LCG rng(12345);

    std::cout << "---------------A: Plain Monte Carlo Integration---------------\n\n";

    // ==============================
    // UNIT CIRCLE
    // ==============================
    auto circle = [](const std::vector<double>& x) {
        double r2 = x[0]*x[0] + x[1]*x[1];
        return (r2 <= 1.0) ? 1.0 : 0.0;
    };

    std::vector<double> a1 = {-1.0, -1.0};
    std::vector<double> b1 = {1.0, 1.0};

    double exact_circle = M_PI;

    std::cout << "# Circle\n";
    std::cout << "# x^2 + y^2 <= 1\n";
    std::cout << "# Exact value: " << exact_circle << "\n";
    std::cout << "# N Value Error ActualError\n";

    for (int k = 2; k <= 7; k++) {
        int N = std::pow(10, k);

        MCResult res = plain_mc(circle, a1, b1, N, [&]() { return rng(); });
        double actual_error = std::abs(res.value - exact_circle);

        std::cout << N << " "
                  << res.value << " "
                  << res.error << " "
                  << actual_error << "\n";
    }
    std::cout << "\n";

    // ==============================
    // GAUSSIAN INTEGRAL
    // ==============================
    auto gaussian = [](const std::vector<double>& x) {
        return std::exp(-(x[0]*x[0] + x[1]*x[1]));
    };

    std::vector<double> a2 = {0.0, 0.0};
    std::vector<double> b2 = {1.0, 1.0};

    double exact_1d = 0.7468241328124271;
    double exact_gaussian = exact_1d * exact_1d;

    std::cout << "# Gaussian\n";
    std::cout << "# exp(-x^2 - y^2)\n";
    std::cout << "# Exact value: " << exact_gaussian << "\n";
    std::cout << "# N Value Error ActualError\n";

    for (int k = 2; k <= 7; k++) {
        int N = std::pow(10, k);

        MCResult res = plain_mc(gaussian, a2, b2, N, [&]() { return rng(); });
        double actual_error = std::abs(res.value - exact_gaussian);

        std::cout << N << " "
                  << res.value << " "
                  << res.error << " "
                  << actual_error << "\n";
    }
    std::cout << "\n";

    // ==============================
    // ELLIPSOID VOLUME
    // ==============================
    double a = 1.0, b = 2.0, c = 3.0;

    auto ellipsoid = [a, b, c](const std::vector<double>& x) {
        double val = (x[0]*x[0])/(a*a)
                   + (x[1]*x[1])/(b*b)
                   + (x[2]*x[2])/(c*c);
        return (val <= 1.0) ? 1.0 : 0.0;
    };

    std::vector<double> a3 = {-a, -b, -c};
    std::vector<double> b3 = { a,  b,  c};

    double exact_ellipsoid = (4.0/3.0) * a * b * c * M_PI;

    std::cout << "# Ellipsoid\n";
    std::cout << "# x^2/a^2 + y^2/b^2 + z^2/c^2 <= 1\n";
    std::cout << "# Exact value: " << exact_ellipsoid << "\n";
    std::cout << "# N Value Error ActualError\n";

    for (int k = 2; k <= 7; k++) {
        int N = std::pow(10, k);

        MCResult res = plain_mc(ellipsoid, a3, b3, N, [&]() { return rng(); });
        double actual_error = std::abs(res.value - exact_ellipsoid);

        std::cout << N << " "
                  << res.value << " "
                  << res.error << " "
                  << actual_error << "\n";
    }
    std::cout << "\n";


    // ==========================================================
    // B: QUASI-RANDOM SEQUENCES
    // ==========================================================
    std::cout << "---------------B: Quasi-Random Sequences---------------\n\n";

    std::mt19937 gen(12345);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    auto std_rng = [&]() {
        return dist(gen);
    };

    // Use smooth 2D function (important!)
    auto f = gaussian;
    std::vector<double> a_qmc = {0.0, 0.0};
    std::vector<double> b_qmc = {1.0, 1.0};
    double exact = exact_gaussian;

    std::ofstream qmc_file("qmc.txt");
    qmc_file << "# N LCG STD QMC\n";

    std::cout << "# N LCG STD QMC\n";

    for (int k = 2; k <= 7; k++) {
        int N = std::pow(10, k);

        auto res_lcg = plain_mc(f, a_qmc, b_qmc, N, [&]() { return rng(); });
        auto res_std = plain_mc(f, a_qmc, b_qmc, N, std_rng);
        auto res_qmc = qmc(f, a_qmc, b_qmc, N);

        double err_lcg = std::abs(res_lcg.value - exact);
        double err_std = std::abs(res_std.value - exact);
        double err_qmc = std::abs(res_qmc.value - exact);

        qmc_file << N << " "
                 << err_lcg << " "
                 << err_std << " "
                 << err_qmc << "\n";

        std::cout << N << " "
                  << err_lcg << " "
                  << err_std << " "
                  << err_qmc << "\n";
    }

    qmc_file.close();

    std::cout << "\n---------------C: Stratified Sampling---------------\n\n";

    std::vector<double> a_strat = {0.0, 0.0};
    std::vector<double> b_strat = {1.0, 1.0};

    // write to separate file (IMPORTANT)
    std::ofstream strat_file("stratified.txt");
    strat_file << "# N PlainMC Stratified\n";

    std::cout << "# N PlainMC Stratified\n";

    for (int k = 2; k <= 7; k++) {
        int N = std::pow(10, k);

        auto res_plain = plain_mc(f, a_strat, b_strat, N, [&]() { return rng(); });
        auto res_strat = stratified_mc(f, a_strat, b_strat, N, [&]() { return rng(); });

        double err_plain = std::abs(res_plain.value - exact);
        double err_strat = std::abs(res_strat.value - exact);

        // write to file (for gnuplot)
        strat_file << N << " "
                << err_plain << " "
                << err_strat << "\n";

        // print to terminal
        std::cout << N << " "
                << err_plain << " "
                << err_strat << "\n";
    }

    strat_file.close();

    std::cout << "\n";

    return 0;
}