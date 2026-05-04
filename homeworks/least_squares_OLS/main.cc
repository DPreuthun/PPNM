#include <iostream>
#include <vector>
#include <cmath>
#include "least_squares.h"
#include <fstream>

int main() {
    // =========================
    // Task A
    // =========================

    std::cout << "\n";
    std::cout << "=========================\n";
    std::cout << "Task A: Ordinary least-squares fit by QR-decomposition\n";
    std::cout << "=========================\n";
    std::cout << "\n";

    // =========================
    // STEP 1: Input data
    // =========================
    std::vector<double> t = {1,2,3,4,6,9,10,13,15};
    std::vector<double> y = {117,100,88,72,53,29.5,25,15.2,11.1};
    std::vector<double> dy = {6,5,4,4,4,3,3,2,2};

    // STEP 2: Log transform
    std::vector<double> logy(y.size());
    std::vector<double> dlogy(y.size());

    for (size_t i = 0; i < y.size(); i++) {
        logy[i] = std::log(y[i]);
        dlogy[i] = dy[i] / y[i];
    }

    // STEP 3: Basis functions
    std::vector<std::function<double(double)>> fs = {
        [](double){ return 1.0; },
        [](double x){ return x; }
    };

    // =========================
    // STEP 4: Fit
    // =========================
    Matrix R(0, 0);
    std::vector<double> c = least_squares_fit(fs, t, logy, dlogy, &R);

    double ln_a = c[0];
    double lambda = -c[1];

    // =========================
    // STEP 5: Results
    // =========================
    std::cout << "Fit results:\n";
    std::cout << "ln(a) = " << ln_a << "\n";
    std::cout << "lambda = " << lambda << "\n";

    double T_half = std::log(2) / lambda;
    std::cout << "Half-life = " << T_half << " days\n";
    std::cout << "modern half-life = " << 3.6316 << " days\n";

    // =========================
    // STEP 6: Write data for plotting
    // =========================
    std::ofstream fout("data.txt");

    for (size_t i = 0; i < t.size(); i++) {
        double y_fit = std::exp(ln_a - lambda * t[i]);
        fout << t[i] << " " << y[i] << " " << dy[i] << " " << y_fit << "\n";
    }

    fout.close();

    // =========================
    // Task B
    // =========================

    std::cout << "\n";
    std::cout << "=========================\n";
    std::cout << "Task B: Uncertainties of the fitting coefficients\n";
    std::cout << "=========================\n";
    std::cout << "\n";

    auto Cov = covariance_matrix(R);

    double sigma_ln_a = std::sqrt(Cov[0][0]);
    double sigma_lambda = std::sqrt(Cov[1][1]);

    std::cout << "ln(a) = " << ln_a << " ± " << sigma_ln_a << "\n";
    std::cout << "lambda = " << lambda << " ± " << sigma_lambda << "\n";

    double sigma_T = std::log(2) / (lambda * lambda) * sigma_lambda;

    std::cout << "Half-life = " << T_half
            << " ± " << sigma_T << " days\n";

    std::cout << "modern half-life = " << 3.6316 << " days\n";
    
    double modern = 3.6316;
    double diff = T_half - modern;

    std::cout << "\nComparison with modern value:\n";
    std::cout << "Difference = " << diff << "\n";
    std::cout << "Difference / uncertainty ≈ " << diff / sigma_T << " sigma\n";

    if (std::abs(diff) < 2 * sigma_T)
        std::cout << "Agreement is reasonable (within ~2 sigma)\n";
    else
        std::cout << "Some deviation (>2 sigma), likely due to experimental uncertainty\n";
    
    // =========================
    // Task C: Evaluation of the quality of the uncertainties of the fit coefficients   
    // =========================

    std::cout << "\n";
    std::cout << "=========================\n";
    std::cout << "Task C: Evaluation of the quality of the uncertainties of the fit coefficients\n";
    std::cout << "=========================\n";
    std::cout << "\n";

    std::cout << "See fit_taskC_variations.png for parameter variation plots.\n";
    std::cout << "\n";

    // File for Task C (parameter variations)
    std::ofstream fout3("fit_variations.txt");

    for (double ti = 0; ti <= 16; ti += 0.1) {

        // Best fit
        double y0 = std::exp(ln_a - lambda * ti);

        // Vary ln(a)
        double y_a_plus  = std::exp((ln_a + sigma_ln_a) - lambda * ti);
        double y_a_minus = std::exp((ln_a - sigma_ln_a) - lambda * ti);

        // Vary lambda
        double y_l_plus  = std::exp(ln_a - (lambda + sigma_lambda) * ti);
        double y_l_minus = std::exp(ln_a - (lambda - sigma_lambda) * ti);

        fout3 << ti << " "
            << y0 << " "
            << y_a_plus << " "
            << y_a_minus << " "
            << y_l_plus << " "
            << y_l_minus << "\n";
    }

    fout3.close();

    return 0;
}