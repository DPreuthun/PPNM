#ifndef RAYLEIGH_H
#define RAYLEIGH_H

#include "matrix.h"

//------------------------------------------------------------
// Structure for storing an eigenpair
//------------------------------------------------------------

struct Eigenpair
{
    double eigenvalue;
    Vector eigenvector;
    int iterations;
};

//------------------------------------------------------------
// Rayleigh quotient
//------------------------------------------------------------

double rayleighQuotient(
    const Matrix& H,
    const Vector& v
);

//------------------------------------------------------------
// Lowest eigenpair
//------------------------------------------------------------

Eigenpair lowestEigenpair(
    const Matrix& H,
    double tolerance = 1e-6,
    int maxIterations = 10000
);

//------------------------------------------------------------
// Second lowest eigenpair
//------------------------------------------------------------

Eigenpair secondEigenpair(
    const Matrix& H,
    const Vector& firstEigenvector,
    double tolerance = 1e-6,
    int maxIterations = 10000
);

#endif