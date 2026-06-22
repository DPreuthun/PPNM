#ifndef HYDROGEN_H
#define HYDROGEN_H

#include "matrix.h"

//------------------------------------------------------------
// Construct the finite-difference Hamiltonian for the
// radial Schrödinger equation of Hydrogen.
//
// n      : number of grid points
// rMax   : maximum radius
//------------------------------------------------------------

Matrix hydrogenHamiltonian(
    int n,
    double rMax
);

#endif