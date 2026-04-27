#include "newton.h"
#include <cmath>
#include "jacobian.h"
#include <iostream>

Vec newton(std::function<Vec(const Vec&)> f,
           Vec x,
           double acc,
           double alpha_min,
           int max_iter) {

    // ✅ allocate once (Part C requirement)
    Mat J(x.size(), Vec(x.size()));

    for (int iter = 0; iter < max_iter; iter++) {
        Vec fx = f(x);

        if (norm(fx) < acc) break;

        // ✅ reuse Jacobian
        jacobian_inplace(f, x, J);

        // Solve J dx = -f
        Vec minus_fx = fx;
        for (auto& v : minus_fx) v = -v;

        Vec dx = solve_linear(J, minus_fx);

        double alpha = 1.0;

        while (true) {
            Vec z = x;
            for (size_t i = 0; i < x.size(); i++)
                z[i] += alpha * dx[i];

            Vec fz = f(z);

            double phi0 = norm(fx);
            double phi_alpha = norm(fz);

            // Armijo condition
            double c = 1e-4;
            if (phi_alpha < (1 - c * alpha) * phi0)
                break;

            if (alpha < alpha_min)
                break;

            // ✅ quadratic interpolation
            double denom = (phi_alpha - phi0 - alpha*phi0);
            double alpha_new = alpha * 0.5; // fallback

            if (std::abs(denom) > 1e-12) {
                double trial = - (alpha*alpha * phi0) / (2*denom);

                // clamp to reasonable range
                if (trial > 0.1 * alpha && trial < 0.9 * alpha)
                    alpha_new = trial;
            }

            alpha = alpha_new;
        }

        // after the while-loop
        if (iter < 5) {
            std::cout << "iter " << iter 
                    << ", final alpha = " << alpha << "\n";
        }

        for (size_t i = 0; i < x.size(); i++)
            x[i] += alpha * dx[i];
    }

    return x;
}