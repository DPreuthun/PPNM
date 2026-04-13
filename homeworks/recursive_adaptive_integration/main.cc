#include <iostream>
#include <iomanip>
#include <cmath>

#include "integrator.h"
#include "erf.h"

int main() {

    std::cout << std::fixed << std::setprecision(10);

    // =========================
    // A
    // =========================
    std::cout << "\n---------A: Recursive open 4-point adaptive integrator--------- \n";

    double acc = 1e-6, eps = 1e-6;

    // ---- Integral 1 ----
    {
        int ncalls = 0;
        auto f = [&](double x) {
            ncalls++;
            return std::sqrt(x);
        };

        double result = integrate(f, 0, 1, acc, eps);
        double exact = 2/3;

        std::cout << "\n1) ∫₀¹ sqrt(x) dx\n";
        std::cout << "Result = " << result << "\n";
        std::cout << "Exact  = " << exact << "\n";
        std::cout << "Error  = " << std::abs(result - exact) << "\n";
        std::cout << "Calls  = " << ncalls << "\n";
        std::cout << ((std::abs(result - exact) < acc) ? "OK\n" : "FAIL\n");
    }

    // ---- Integral 2 ----
    {
        int ncalls = 0;
        auto f = [&](double x) {
            ncalls++;
            return 1/std::sqrt(x);
        };

        double result = integrate(f, 0, 1, acc, eps);
        double exact = 2;

        std::cout << "\n2) ∫₀¹ 1/sqrt(x) dx\n";
        std::cout << "Result = " << result << "\n";
        std::cout << "Exact  = " << exact << "\n";
        std::cout << "Error  = " << std::abs(result - exact) << "\n";
        std::cout << "Calls  = " << ncalls << "\n";
        std::cout << ((std::abs(result - exact) < acc) ? "OK\n" : "FAIL\n");
    }

    // ---- Integral 3 ----
    {
        int ncalls = 0;
        auto f = [&](double x) {
            ncalls++;
            return std::sqrt(1-x*x);
        };

        double result = integrate(f, 0, 1, acc, eps);
        double exact = 0.7853981634; // known value

        std::cout << "\n3) ∫₀¹ sqrt(1-x^2) dx\n";
        std::cout << "Result = " << result << "\n";
        std::cout << "Exact  = " << exact << "\n";
        std::cout << "Error  = " << std::abs(result - exact) << "\n";
        std::cout << "Calls  = " << ncalls << "\n";
        std::cout << ((std::abs(result - exact) < acc) ? "OK\n" : "FAIL\n");
    }

    // ---- Integral 4 ----
    {
        int ncalls = 0;
        auto f = [&](double x) {
            ncalls++;
            return std::log(x)/std::sqrt(x);
        };

        double result = integrate(f, 0, 1, acc, eps);
        double exact = 4; // known value

        std::cout << "\n4) ∫₀¹ ln(x)/sqrt(x) dx\n";
        std::cout << "Result = " << result << "\n";
        std::cout << "Exact  = " << exact << "\n";
        std::cout << "Error  = " << std::abs(result - exact) << "\n";
        std::cout << "Calls  = " << ncalls << "\n";
        std::cout << ((std::abs(result - exact) < acc) ? "OK\n" : "FAIL\n");
    }


    // erf convergence study
    std::cout << "\nerf convergence\n";

    double exact = 0.84270079294971486934;

    // Print clean data block for plotting
    std::cout << "\n# acc error\n";

    for (double acc = 1e-1; acc >= 1e-6; acc /= 10) {
        double val = erf_integral(1.0, acc, 0.0);
        double err = std::abs(val - exact);

        std::cout << acc << " " << err << "\n";
    }

    std::cout << "\n---------B: Variable transformation quadratures---------\n";
    std::cout << "\n";

    // =======================
    // Test 1: 1/sqrt(x)
    // =======================
    {
        std::cout << "Integral: ∫₀¹ dx 1/sqrt(x)\n";

        auto f = [](double x) {
            if (x < 1e-12) x = 1e-12;
            return 1/std::sqrt(x);
        };

        int calls_std = 0;
        auto f_std = [&](double x) {
            calls_std++;
            return f(x);
        };

        double res_std = integrate(f_std, 0, 1, 1e-6, 1e-6);

        int calls_cc = 0;
        auto f_cc = [&](double x) {
            calls_cc++;
            return f(x);
        };

        double res_cc = integrate_cc(f_cc, 0, 1, 1e-6, 1e-6);

        std::cout << "Standard: " << res_std << " calls = " << calls_std << "\n";
        std::cout << "CC      : " << res_cc << " calls = " << calls_cc << "\n";
        std::cout << "Numpy   : " << 1.9999999999999984 << " calls = " << 231 << "\n";
        std::cout << "Exact   : 2\n\n";
    }

    // =======================
    // Test 2: ln(x)/sqrt(x)
    // =======================
    {
        std::cout << "Integral: ∫₀¹ dx ln(x)/sqrt(x)\n";

        auto f = [](double x) {
            if (x < 1e-12) x = 1e-12;
            return std::log(x)/std::sqrt(x);
        };

        int calls_std = 0;
        auto f_std = [&](double x) {
            calls_std++;
            return f(x);
        };

        double res_std = integrate(f_std, 0, 1, 1e-6, 1e-6);

        int calls_cc = 0;
        auto f_cc = [&](double x) {
            calls_cc++;
            return f(x);
        };

        double res_cc = integrate_cc(f_cc, 0, 1, 1e-6, 1e-6);

        std::cout << "Standard: " << res_std << " calls = " << calls_std << "\n";
        std::cout << "CC      : " << res_cc << " calls = " << calls_cc << "\n";
        std::cout << "Numpy   : " << -4.000000000000085 << " calls = " << 315 << "\n";
        std::cout << "Exact   : -4\n\n";
    }

    std::cout << "\nIntegral: ∫0->inf dx exp(-x)\n";

    int calls = 0;
    auto f = [&](double x) {
        calls++;
        return std::exp(-x);
    };

    double res = integrate_inf(f, 0, 1e-6, 1e-6);

    std::cout << "Result = " << res << "\n";
    std::cout << "Exact  = 1\n";
    std::cout << "Calls  = " << calls << "\n";
    std::cout << "\n";
    std::cout << "Numpy: \n";
    std::cout << "Result = " << 1.0000000000000002 << "\n";
    std::cout << "Exact  = 1\n";
    std::cout << "Calls  = " << 135 << "\n";

    std::cout << "\nIntegral: ∫0->inf dx 1/(1+x^2)\n";

    int calls2 = 0;
    auto f2 = [&](double x) {
        calls2++;
        return 1/(1 + x*x);
    };

    double res2 = integrate_inf(f2, 0, 1e-6, 1e-6);

    std::cout << "Result = " << res2 << "\n";
    std::cout << "Exact  = " << M_PI/2 << "\n";
    std::cout << "Calls  = " << calls2 << "\n";
    std::cout << "\n";
    std::cout << "Numpy: \n";
    std::cout << "Result = " << 1.5707963267948966 << "\n";
    std::cout << "Exact  = " << M_PI/2 << "\n";
    std::cout << "Calls  = " << 45 << "\n";

    {
    std::cout << "\n---------C: Error estimate test---------\n";
    std::cout << "\n";

    // =========================
    // Test 1
    // =========================
    {
        std::cout << "Integral: ∫₀¹ ln(x)/sqrt(x) dx\n";

        auto f = [](double x) {
            if (x < 1e-12) x = 1e-12;
            return std::log(x)/std::sqrt(x);
        };

        auto result = integrate_err(f, 0, 1, 1e-6, 1e-6);
        double exact = -4;

        std::cout << "Result          = " << result.first << "\n";
        std::cout << "Excat           = " << exact << "\n";
        std::cout << "Estimated error = " << result.second << "\n";
        std::cout << "Actual error    = " << std::abs(result.first - exact) << "\n\n";
    }

    // =========================
    // Test 2
    // =========================
    {
        std::cout << "Integral: ∫₀¹ 1/sqrt(x) dx\n";

        auto f = [](double x) {
            if (x < 1e-12) x = 1e-12;
            return 1/std::sqrt(x);
        };

        auto result = integrate_err(f, 0, 1, 1e-6, 1e-6);
        double exact = 2;

        std::cout << "Result          = " << result.first << "\n";
        std::cout << "Excat           = " << exact << "\n";
        std::cout << "Estimated error = " << result.second << "\n";
        std::cout << "Actual error    = " << std::abs(result.first - exact) << "\n\n";
    }

    // =========================
    // Test 3
    // =========================
    {
        std::cout << "Integral: ∫₀¹ sqrt(1-x^2) dx\n";

        auto f = [](double x) {
            return std::sqrt(1 - x*x);
        };

        auto result = integrate_err(f, 0, 1, 1e-6, 1e-6);
        double exact = M_PI / 4;

        std::cout << "Result          = " << result.first << "\n";
        std::cout << "Excat           = " << exact << "\n";
        std::cout << "Estimated error = " << result.second << "\n";
        std::cout << "Actual error    = " << std::abs(result.first - exact) << "\n\n";
    }
    }

    return 0;
}