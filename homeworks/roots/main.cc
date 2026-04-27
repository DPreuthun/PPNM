#include <iostream>
#include <fstream>
#include <cmath>
#include "newton.h"
#include "hydrogen.h"

int main() {
    std::cout << "\n";
    std::cout << "----------- A: Newton's method with numerical Jacobian and back-tracking line-search -----------\n";
    std::cout << "\n";

    // Rosenbrock gradient
    auto rosen_grad = [](const Vec& v) -> Vec {
        double x = v[0], y = v[1];
        return {
            -2*(1 - x) - 400*x*(y - x*x),
            200*(y - x*x)
        };
    };

    // Himmelblau gradient
    auto himmel_grad = [](const Vec& v) -> Vec {
        double x = v[0], y = v[1];
        return {
            4*x*(x*x + y - 11) + 2*(x + y*y - 7),
            2*(x*x + y - 11) + 4*y*(x + y*y - 7)
        };
    };

    // Initial guesses
    Vec x1 = {1.0, 1.0};
    Vec sol1 = newton(rosen_grad, x1);

    std::cout << "Found Rosenbrock minimum: "
              << sol1[0] << ", " << sol1[1] << "\n";

    std::cout << "Exact Rosenbrock minimum: "
              << 1 << ", " << 1 << "\n";

    Vec x2 = {0.0, 0.0};
    Vec sol2 = newton(himmel_grad, x2);

    std::cout << "Found Himmelblau minimum: "
              << sol2[0] << ", " << sol2[1] << "\n";

    std::cout << "Exact Rosenbrock minimum: "
              << -0.270745 << ", " << -0.923039 << "\n";

    std::cout << "\n";
    std::cout << "----------- B: Bound states of hydrogen atom with shooting method for boundary value problems -----------\n";
    std::cout << "\n";

    double E = find_ground_state(1e-3, 8.0, 0.001);

    std::cout << "Found E0 = " << E << "\n";
    std::cout << "Exact E0 = -0.5\n";

    std::vector<double> r, f;
    compute_wavefunction(E, r, f);

    // ---------- convergence rmax ----------
    std::ofstream conv_rmax("conv_rmax.txt");

    for (double rmax = 4; rmax <= 12; rmax += 1.0) {
        double E = find_ground_state(1e-3, rmax, 0.001);

        if (!std::isnan(E)) {
            conv_rmax << rmax << " " << fabs(E + 0.5) << "\n";
        }
    }

    // ---------- convergence rmin ----------
    std::ofstream conv_rmin("conv_rmin.txt");

    for (double rmin = 1e-1; rmin >= 1e-5; rmin *= 0.5) {
        double E = find_ground_state(rmin, 8.0, 0.001);

        if (!std::isnan(E)) {
            conv_rmin << rmin << " " << fabs(E + 0.5) << "\n";
        }
    }

    // ---------- convergence h ----------
    std::ofstream conv_h("conv_h.txt");

    for (double h = 0.2; h >= 1e-4; h *= 0.7) {
        double E = find_ground_state(1e-3, 8.0, h);

        if (!std::isnan(E)) {
            conv_h << h << " " << fabs(E + 0.5) << "\n";
        }
    }

    // ---------- wavefunction ----------
    std::ofstream file("wave.txt");

    for (size_t i = 0; i < r.size(); i++) {
        double exact = r[i] * exp(-r[i]);
        file << r[i] << " " << f[i] << " " << exact << "\n";
    }

    std::cout << "\n";
    std::cout << "----------- C: Quadratic interpolation line-search -----------\n";
    std::cout << "\n";

    std::cout << "Demonstrating quadratic line search behavior:\n";
    std::cout << "The step size alpha should NOT decrease by simple halving.\n";
    std::cout << "Instead, it should vary based on quadratic interpolation.\n\n";
    std::cout << "Using Rosenbrock function with initial guess (1.2, 1.0) for demonstration:\n";

    // Run Newton once (same test problem)
    Vec x_demo = {1.2, 1.0};
    Vec sol_demo = newton(rosen_grad, x_demo);

    std::cout << "\nFinal solution: "
            << sol_demo[0] << ", " << sol_demo[1] << "\n";
    
    std::cout << "\nExact solution: "
            << 1 << ", " << 1 << "\n";

    std::cout << "\n";
    return 0;
}