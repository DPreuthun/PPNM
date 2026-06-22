#include "hydrogen.h"

//------------------------------------------------------------
// Construct Hydrogen Hamiltonian
//
// H = -1/2 d²/dr² - 1/r
//
// Second-order central finite difference.
//
// Boundary conditions:
//      u(0)=0
//      u(rMax)=0
//------------------------------------------------------------

Matrix hydrogenHamiltonian(int n, double rMax)
{
    Matrix H(n, n);

    double h = rMax / (n + 1);
    double kinetic = 1.0 / (h * h);

    for (int i = 0; i < n; i++)
    {
        double r = (i + 1) * h;

        // Diagonal
        H(i, i) = kinetic - 1.0 / r;

        // Upper diagonal
        if (i < n - 1)
            H(i, i + 1) = -0.5 * kinetic;

        // Lower diagonal
        if (i > 0)
            H(i, i - 1) = -0.5 * kinetic;
    }

    return H;
}