#include <iostream>
#include <fstream>
#include <cmath>
#include "vecmatrix.h"
#include "splines.h"

using namespace pp;

// 🔹 Helper function for quadratic spline tests
void qspline_test(const char* datafile,
                  const char* ptsfile,
                  int type)
{
    int n = 5;
    vector x(n), y(n);

    for (int i = 0; i < n; i++) {
        x[i] = i + 1;

        if (type == 0) y[i] = 1;               // constant
        if (type == 1) y[i] = x[i];            // linear
        if (type == 2) y[i] = x[i]*x[i];       // quadratic
    }

    qspline s(x,y);

    std::ofstream data(datafile);
    std::ofstream pts(ptsfile);

    // save original points
    for (int i = 0; i < n; i++)
        pts << x[i] << " " << y[i] << "\n";

    // dense sampling
    for (double z = x[0]; z <= x[n-1] + 1e-10; z += 0.01) {
        data << z << " "
             << s.eval(z) << " "
             << s.deriv(z) << " "
             << s.integ(z) << "\n";
    }
}


int main() {
    // ================= LINEAR SPLINE TEST =================
    int n = 19; // 0 to 9 in steps of 0.5
    vector x(n), y(n);

    for (int i = 0; i < n; i++) {
        x[i] = 0.5 * i;
        y[i] = cos(x[i]);
    }

    std::ofstream interpFile("interp.dat");
    std::ofstream integFile("integ.dat");

    for (double z = 0; z <= 9; z += 0.01) {
        double s = linterp(x, y, z);
        double S = linterpInteg(x, y, z);

        interpFile << z << " " << s << "\n";
        integFile << z << " " << S << " " << sin(z) << "\n";
    }

    std::ofstream dataFile("data.dat");
    for (int i = 0; i < n; i++) {
        dataFile << x[i] << " " << y[i] << "\n";
    }


    // ================= QUADRATIC SPLINE TESTS =================

    qspline_test("const.dat",  "const_pts.dat",  0);
    qspline_test("linear.dat", "linear_pts.dat", 1);
    qspline_test("quad.dat",   "quad_pts.dat",   2);

    std::cout << "See plots for results.\n";

    return 0;
}