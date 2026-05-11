#include "complex_tasks.h"
#include "approx.h"

#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>

void complexExercises() {

    using namespace std;

    cout << fixed << setprecision(10);

    cout << "===== COMPLEX NUMBERS =====\n\n";

    complex<double> i(0, 1);

    // sqrt(-1)
    complex<double> sqrt_minus1 = sqrt(complex<double>(-1, 0));

    cout << "sqrt(-1) = " << sqrt_minus1 << "\n";

    // sqrt(i)
    complex<double> sqrt_i = sqrt(i);

    cout << "sqrt(i) = " << sqrt_i << "\n";

    // e^i
    complex<double> exp_i = exp(i);

    cout << "e^i = " << exp_i << "\n";

    // e^(i*pi)
    complex<double> euler = exp(i * M_PI);

    cout << "e^(i*pi) = " << euler << "\n";

    // i^i
    complex<double> i_pow_i = pow(i, i);

    cout << "i^i = " << i_pow_i << "\n";

    // ln(i)
    complex<double> ln_i = log(i);

    cout << "ln(i) = " << ln_i << "\n";

    // sin(i*pi)
    complex<double> sin_ipi = sin(i * M_PI);

    cout << "sin(i*pi) = " << sin_ipi << "\n\n";

    cout << "===== CHECKS =====\n\n";

    // Expected sqrt(-1) = i
    cout << "sqrt(-1) approx i ? "
         << (approx(sqrt_minus1, i) ? "true" : "false")
         << "\n";

    // Expected e^(i*pi) = -1
    cout << "e^(i*pi) approx -1 ? "
         << (approx(euler, complex<double>(-1,0)) ? "true" : "false")
         << "\n";

    // Expected ln(i) = i*pi/2
    complex<double> expected_ln_i(0, M_PI/2);

    cout << "ln(i) approx i*pi/2 ? "
         << (approx(ln_i, expected_ln_i) ? "true" : "false")
         << "\n";

    // Expected i^i = e^(-pi/2)
    double expected_i_pow_i = exp(-M_PI/2);

    cout << "i^i approx e^(-pi/2) ? "
         << (approx(i_pow_i,
                    complex<double>(expected_i_pow_i,0))
             ? "true" : "false")
         << "\n";
}