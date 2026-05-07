#include <iostream>
#include <fstream>
#include <cmath>

#include "ode.h"
#include "systems.h"

int main(){

    std::cout << "\n";
    std::cout << "=======================================\n";
    std::cout << "Part A: Embedded rule Runge-Kutta ODE integrator\n";
    std::cout << "=======================================\n\n";

    std::cout << "**** TEST 1: Harmonic oscillator\n";
    std::cout << "Equation: u'' = -u\n";
    std::cout << "See oscillator.png\n\n";

    vector y0 = {1,0};

    auto [xlist1, ylist1] =
        driver(oscillator,0,20,y0);

    std::ofstream file1("oscillator_data.txt");

    for(size_t i=0;i<xlist1.size();i++){

        double t = xlist1[i];

        file1
            << t << " "
            << ylist1[i][0] << " "
            << exact_oscillator(t)
            << "\n";
    }

    file1.close();

    std::cout << "Initial conditions:\n";
    std::cout << "u(0)=1\n";
    std::cout << "u'(0)=0\n\n";

    std::cout << "Accepted steps: "
              << xlist1.size()
              << "\n";

    std::cout << "Numerical u(20) = "
              << ylist1.back()[0]
              << "\n";

    std::cout << "Exact cos(20)   = "
              << std::cos(20)
              << "\n\n";

    std::cout << "**** TEST 2: Damped oscillator\n";
    std::cout << "Equation: u'' + b*u' + c*u = 0\n";
    std::cout << "See damped.png\n\n";

    vector y1 = {1,0};

    auto [xlist2, ylist2] =
        driver(damped_oscillator,0,20,y1);

    std::ofstream file2("damped_data.txt");

    for(size_t i=0;i<xlist2.size();i++){

        double t = xlist2[i];

        file2
            << t << " "
            << ylist2[i][0] << " "
            << exact_damped(t)
            << "\n";
    }

    file2.close();

    std::cout << "Parameters:\n";
    std::cout << "b = 0.25\n";
    std::cout << "c = 5.0\n\n";

    std::cout << "Initial conditions:\n";
    std::cout << "u(0)=1\n";
    std::cout << "u'(0)=0\n\n";

    std::cout << "Accepted steps: "
              << xlist2.size()
              << "\n";

    double numerical = ylist2.back()[0];
    double exact = exact_damped(20);

    std::cout << "Final numerical value:\n";
    std::cout << "u(20) numerical = "
            << numerical
            << "\n";

    std::cout << "u(20) exact     = "
            << exact
            << "\n\n";

    /////////////////////////////////////////////////////////////////////////

    std::cout << "**** TEST 3: SciPy odeint pendulum example\n";
    std::cout << "Equation:\n";
    std::cout << "theta'' + b*theta' + c*sin(theta) = 0\n";
    std::cout << "See pendulum.png\n\n";

    double pi = std::acos(-1);

    vector y2 = {0.1, 0.0};

    auto [xlist3, ylist3] =
        driver(pendulum,0,10,y2);

    std::ofstream file3("pendulum_data.txt");

    for(size_t i=0;i<xlist3.size();i++){

        double t = xlist3[i];

        file3
            << t << " "
            << ylist3[i][0] << " "
            << exact_pendulum(t)
            << "\n";
    }

    file3.close();

    std::cout << "Parameters:\n";
    std::cout << "b = 0.25\n";
    std::cout << "c = 5.0\n\n";

    std::cout << "Initial conditions:\n";
    std::cout << "theta(0) =  " << y2[0]
              << "\n";

    std::cout << "omega(0) = " << y2[1]
              << "\n\n";

    std::cout << "Accepted steps: "
            << xlist3.size()
            << "\n";

    double numerical_theta = ylist3.back()[0];
    double exact_theta = exact_pendulum(10);

    double numerical_omega = ylist3.back()[1];
    double exact_omega = exact_pendulum_velocity(10);

    std::cout << "Final values at t=10:\n";

    std::cout << "theta(10) numerical = "
            << numerical_theta
            << "\n";

    std::cout << "theta(10) exact     = "
            << exact_theta
            << "\n\n";

    std::cout << "omega(10) numerical = "
            << numerical_omega
            << "\n";

    std::cout << "omega(10) exact     = "
            << exact_omega
            << "\n\n";

    /////////////////////////////////////////////////////////////////////////

    std::cout << "=======================================\n";
    std::cout << "Part B: Relativistic planetary orbit\n";
    std::cout << "=======================================\n\n";

    std::cout << "**** CASE 1: Newtonian circular orbit\n";
    std::cout << "See circle.png\n\n";

    epsilon = 0.0;

    vector orbit1 = {1.0, 0.0};

    auto [phi1, y1_orbit] =
        driver(
            relativistic_orbit,
            0,
            50,
            orbit1,
            0.001,
            1e-12,
            1e-12
        );

    std::ofstream file1_orbit("orbit_circle.txt");

    for(double phi=0; phi<=50; phi+=0.01){

        double x = std::cos(phi);

        double y = std::sin(phi);

        file1_orbit
            << x << " "
            << y << "\n";
    }

    file1_orbit.close();

    std::cout << "epsilon = 0\n";
    std::cout << "u(0)=1\n";
    std::cout << "u'(0)=0\n";

    std::cout << "Accepted steps: "
            << phi1.size()
            << "\n\n";

    std::cout << "**** CASE 2: Newtonian elliptical orbit\n";
    std::cout << "See ellipse.png\n\n";

    epsilon = 0.0;

    vector orbit2 = {1.0, -0.5};

    auto [phi2, y2_orbit] =
        driver(
            relativistic_orbit,
            0,
            50,
            orbit2,
            0.01,
            1e-6,
            1e-6
        );

    std::ofstream file2_orbit("orbit_ellipse.txt");

    for(size_t i=0;i<phi2.size();i++){

        double phi = phi2[i];

        double u = y2_orbit[i][0];

        double r = 1.0/u;

        double x = r*std::cos(phi);

        double y = r*std::sin(phi);

        file2_orbit
            << x << " "
            << y << "\n";
    }

    file2_orbit.close();

    std::cout << "epsilon = 0\n";
    std::cout << "u(0)=1\n";
    std::cout << "u'(0)=-0.5\n";

    std::cout << "Accepted steps: "
            << phi2.size()
            << "\n\n";

    //
    // ---------------------------------------------------------
    // CASE 3
    // Relativistic precession
    // epsilon = 0.01
    // u'(0)=-0.5
    // ---------------------------------------------------------
    //

    std::cout << "**** CASE 3: Relativistic precession\n";
    std::cout << "See precession.png\n\n";

    epsilon = 0.01;

    vector orbit3 = {1.0, -0.5};

    auto [phi3, y3_orbit] =
        driver(relativistic_orbit,0,200,orbit3);

    std::ofstream file3_orbit("orbit_precession.txt");

    for(size_t i=0;i<phi3.size();i++){

        double phi = phi3[i];

        double u = y3_orbit[i][0];

        double r = 1.0/u;

        double x = r*std::cos(phi);

        double y = r*std::sin(phi);

        file3_orbit
            << x << " "
            << y << "\n";
    }

    file3_orbit.close();

    std::cout << "epsilon = 0.01\n";
    std::cout << "u(0)=1\n";
    std::cout << "u'(0)=-0.5\n";

    std::cout << "Accepted steps: "
            << phi3.size()
            << "\n\n";

    /////////////////////////////////////////////////////////////////////////

    std::cout << "=======================================\n";
    std::cout << "Part C: Three-body figure-8 orbit\n";
    std::cout << "=======================================\n\n";

    //
    // Initial conditions
    // Chenciner-Montgomery figure-8
    //

    vector z0 = {

        0.4662036850,  0.4323657300,
        0.4662036850,  0.4323657300,
        -0.93240737,   -0.86473146,

        -0.97000436,    0.24308753,
        0.97000436,   -0.24308753,
        0.0,           0.0
    };

    auto [tlist, zlist] =
        driver(
            threebody,
            0,
            20,
            z0,
            0.001,
            1e-6,
            1e-6
        );

    std::ofstream bodyfile("threebody.txt");

    for(size_t i=0;i<tlist.size();i++){

        bodyfile

            << zlist[i][6]  << " "
            << zlist[i][7]  << " "

            << zlist[i][8]  << " "
            << zlist[i][9]  << " "

            << zlist[i][10] << " "
            << zlist[i][11]

            << "\n";
    }

    bodyfile.close();

    std::cout << "Integrated figure-8 solution\n";
    std::cout << "See threebody.png\n\n";

    std::cout << "Accepted steps: "
            << tlist.size()
            << "\n\n";

    return 0;
}