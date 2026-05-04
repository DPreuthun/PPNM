#pragma once
#include <vector>

using Vec = std::vector<double>;

double shooting_function(double E, double rmin, double rmax, double h);
double find_ground_state(double rmin, double rmax, double h);

void compute_wavefunction(double E,
                          std::vector<double>& r_vals,
                          std::vector<double>& f_vals);