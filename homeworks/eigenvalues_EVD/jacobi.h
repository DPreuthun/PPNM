#ifndef JACOBI_H
#define JACOBI_H

#include "vecmatrix.h"

namespace pp {

void timesJ(matrix& A, int p, int q, double theta);
void Jtimes(matrix& A, int p, int q, double theta);

int jacobi(matrix& A, matrix& V);

}

#endif