#include <iostream>
#include <fstream>
#include <iomanip>

#include "sfuns.h"

int main() {

    std::ofstream erf_file("erf_data.txt");
    std::ofstream gamma_file("gamma_data.txt");
    std::ofstream lngamma_file("lngamma_data.txt");

    erf_file << std::fixed << std::setprecision(10);
    gamma_file << std::fixed << std::setprecision(10);
    lngamma_file << std::fixed << std::setprecision(10);

    // erf(x)
    for (double x = -3; x <= 3; x += 0.01) {

        erf_file
            << x << " "
            << erf_approx(x) << "\n";
    }

    // Gamma(x)
    for (double x = 0.1; x <= 10; x += 0.01) {

        gamma_file
            << x << " "
            << gamma_function(x) << "\n";
    }

    // lnGamma(x)
    for (double x = 0.1; x <= 10; x += 0.01) {

        lngamma_file
            << x << " "
            << lngamma_function(x) << "\n";
    }

    std::cout << "Data files generated.\n";

    return 0;
}