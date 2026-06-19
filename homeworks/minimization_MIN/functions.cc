#include "functions.h"
#include <cmath>

double rosenbrock(const Vector& x){
    return pow(1-x[0],2)+100*pow(x[1]-x[0]*x[0],2);
}

double himmelblau(const Vector& x){
    return pow(x[0]*x[0]+x[1]-11,2)
          +pow(x[0]+x[1]*x[1]-7,2);
}