#pragma once

#include <cmath>
#include "ode.h"

extern double epsilon;

double exact_oscillator(double t);

vector oscillator(double x, vector y);

vector damped_oscillator(double x, vector y);

double exact_damped(double x);

vector pendulum(double t, vector y);

double exact_pendulum(double t);

double exact_pendulum_velocity(double t);

vector relativistic_orbit(double phi, vector y);

vector threebody(double t, vector z);