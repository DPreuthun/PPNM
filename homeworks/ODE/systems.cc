#include "systems.h"

double exact_oscillator(double t){
    return std::cos(t);
}

vector oscillator(double x, vector y){

    vector dydx(2);

    dydx[0] = y[1];
    dydx[1] = -y[0];

    return dydx;
}

//
// Damped oscillator
// u'' + b*u' + c*u = 0
//
vector damped_oscillator(double x, vector y){

    double b = 0.25;
    double c = 5.0;

    vector dydx(2);

    dydx[0] = y[1];
    dydx[1] = -b*y[1] - c*y[0];

    return dydx;
}

double exact_damped(double x){

    double b = 0.25;
    double c = 5.0;

    double omega =
        std::sqrt(c - b*b/4.0);

    double A = 1.0;

    double B = b/(2.0*omega);

    return std::exp(-b*x/2.0) *
        (
            A*std::cos(omega*x)
            + B*std::sin(omega*x)
        );
}

vector pendulum(double t, vector y){

    double b = 0.25;
    double c = 5.0;

    double theta = y[0];
    double omega = y[1];

    vector dydt(2);

    dydt[0] = omega;

    dydt[1] =
        -b*omega
        -c*std::sin(theta);

    return dydt;
}

double exact_pendulum(double t){

    double b = 0.25;
    double c = 5.0;

    double theta0 = 0.1;

    double omega =
        std::sqrt(c - b*b/4.0);

    double A = theta0;

    double B =
        (b*theta0)/(2.0*omega);

    return
        std::exp(-b*t/2.0)
        *
        (
            A*std::cos(omega*t)
            + B*std::sin(omega*t)
        );
}

double exact_pendulum_velocity(double t){

    double b = 0.25;
    double c = 5.0;

    double theta0 = 0.1;

    double omega =
        std::sqrt(c - b*b/4.0);

    double A = theta0;

    double B =
        (b*theta0)/(2.0*omega);

    double exp_part =
        std::exp(-b*t/2.0);

    double trig_part =
        -A*omega*std::sin(omega*t)
        + B*omega*std::cos(omega*t);

    double damping_part =
        -(b/2.0)
        *
        (
            A*std::cos(omega*t)
            + B*std::sin(omega*t)
        );

    return exp_part*(trig_part + damping_part);
}

double epsilon = 0.01;

vector relativistic_orbit(double phi, vector y){

    double u  = y[0];
    double up = y[1];

    vector dydphi(2);

    dydphi[0] = up;

    dydphi[1] =
        1.0
        - u
        + epsilon*u*u;

    return dydphi;
}

vector threebody(double t, vector z){

    vector dzdt(12);

    //
    // Velocities
    //

    double vx1 = z[0];
    double vy1 = z[1];

    double vx2 = z[2];
    double vy2 = z[3];

    double vx3 = z[4];
    double vy3 = z[5];

    //
    // Positions
    //

    double x1 = z[6];
    double y1 = z[7];

    double x2 = z[8];
    double y2 = z[9];

    double x3 = z[10];
    double y3 = z[11];

    //
    // Relative vectors
    //

    double dx12 = x2-x1;
    double dy12 = y2-y1;

    double dx13 = x3-x1;
    double dy13 = y3-y1;

    double dx23 = x3-x2;
    double dy23 = y3-y2;

    //
    // Distances
    //

    double r12 =
        std::pow(dx12*dx12 + dy12*dy12,1.5);

    double r13 =
        std::pow(dx13*dx13 + dy13*dy13,1.5);

    double r23 =
        std::pow(dx23*dx23 + dy23*dy23,1.5);

    //
    // Accelerations
    //

    double ax1 =
        dx12/r12 + dx13/r13;

    double ay1 =
        dy12/r12 + dy13/r13;

    double ax2 =
        -dx12/r12 + dx23/r23;

    double ay2 =
        -dy12/r12 + dy23/r23;

    double ax3 =
        -dx13/r13 - dx23/r23;

    double ay3 =
        -dy13/r13 - dy23/r23;

    //
    // z' = {accelerations, velocities}
    //

    dzdt[0] = ax1;
    dzdt[1] = ay1;

    dzdt[2] = ax2;
    dzdt[3] = ay2;

    dzdt[4] = ax3;
    dzdt[5] = ay3;

    dzdt[6] = vx1;
    dzdt[7] = vy1;

    dzdt[8] = vx2;
    dzdt[9] = vy2;

    dzdt[10] = vx3;
    dzdt[11] = vy3;

    return dzdt;
}