#include "hydrogen.h"
#include <cmath>
#include <functional>
#include <iostream>

// ---------- RK4 STEP ----------
static Vec rk4_step(std::function<Vec(double, const Vec&)> f,
                    double r,
                    const Vec& y,
                    double h) {

    Vec k1 = f(r, y);

    Vec y2(2);
    for (int i = 0; i < 2; i++) y2[i] = y[i] + 0.5*h*k1[i];
    Vec k2 = f(r + 0.5*h, y2);

    Vec y3(2);
    for (int i = 0; i < 2; i++) y3[i] = y[i] + 0.5*h*k2[i];
    Vec k3 = f(r + 0.5*h, y3);

    Vec y4(2);
    for (int i = 0; i < 2; i++) y4[i] = y[i] + h*k3[i];
    Vec k4 = f(r + h, y4);

    Vec yn(2);
    for (int i = 0; i < 2; i++)
        yn[i] = y[i] + h/6*(k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);

    return yn;
}

// ---------- SHOOTING FUNCTION ----------
double shooting_function(double E, double rmin, double rmax, double h) {

    double f0 = rmin;
    double g0 = 1.0;

    Vec y = {f0, g0};

    auto ode = [E](double r, const Vec& y) -> Vec {
        return {
            y[1],
            -2*(E + 1.0/r)*y[0]
        };
    };

    double r = rmin;
    while (r < rmax) {
        y = rk4_step(ode, r, y, h);
        r += h;
    }

    return y[0]; // M(E)
}

// ---------- ROOT FINDING (Bisection) ----------
double find_ground_state(double rmin, double rmax, double h) {

    double E_low  = -1.0;
    double E_high = -0.1;

    double M_low  = shooting_function(E_low,  rmin, rmax, h);
    double M_high = shooting_function(E_high, rmin, rmax, h);

    // Ensure root is bracketed
    if (M_low * M_high > 0) {
        // return NaN to signal failure
        return NAN;
    }

    for (int i = 0; i < 100; i++) {
        double E_mid = 0.5 * (E_low + E_high);
        double M_mid = shooting_function(E_mid, rmin, rmax, h);

        if (fabs(M_mid) < 1e-10)
            return E_mid;

        if (M_low * M_mid < 0) {
            E_high = E_mid;
            M_high = M_mid;
        } else {
            E_low = E_mid;
            M_low = M_mid;
        }
    }

    return 0.5 * (E_low + E_high);
}

// ---------- WAVEFUNCTION ----------
void compute_wavefunction(double E,
                          std::vector<double>& r_vals,
                          std::vector<double>& f_vals) {

    double rmin = 1e-3;
    double rmax = 8.0;
    double h = 0.001;

    Vec y = {rmin, 1.0};

    auto ode = [E](double r, const Vec& y) -> Vec {
        return {
            y[1],
            -2*(E + 1.0/r)*y[0]
        };
    };

    double r = rmin;
    while (r < rmax) {
        r_vals.push_back(r);
        f_vals.push_back(y[0]);

        y = rk4_step(ode, r, y, h);
        r += h;
    }
}