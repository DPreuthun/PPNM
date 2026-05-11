#ifndef APPROX_H
#define APPROX_H

bool approx(double a,
            double b,
            double acc = 1e-9,
            double eps = 1e-9);

void compareDoubles();

#endif