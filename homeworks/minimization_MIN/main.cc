#include <iostream>
#include "newton.h"
#include "functions.h"
#include "higgs.h"

int main(){

    std::cout << "\n" << "-----------------------------------------------------------" << "\n";
    std::cout << "A: Newton's method with numerical gradient, numerical Hessian matrix and back-tracking linesearch" << "\n";
    std::cout << "-----------------------------------------------------------" << "\n\n";

    Vector x(2);
    int steps;

    x[0]=-2;
    x[1]=5;

    Vector r=newton(rosenbrock,x,1e-3,steps);

    int forwardRosenSteps = steps;
    double forwardRosenValue = rosenbrock(r);

    std::cout<<"Found Rosenbrock minimum (a=1, b=100):\n";
    std::cout<<r<<"\n";
    std::cout<<"Exact Rosenbrock minimum (a=1, b=100):\n";
    std::cout<<"1 1\n";
    std::cout<<"Steps = "<<forwardRosenSteps<<"\n\n";

    x[0]=5;
    x[1]=5;

    Vector h=newton(himmelblau,x,1e-3,steps);

    int forwardHimmelSteps = steps;
    double forwardHimmelValue = himmelblau(h);

    std::cout<<"Found Himmelblau minimum:\n";
    std::cout<<h<<"\n";
    std::cout<<"Exact Himmelblau minimum:\n";
    std::cout<<"3 2 or -2.805118 3.131312 or -3.779310 -3.283186 or 3.584428 -1.848126\n";
    std::cout<<"Steps = "<<forwardHimmelSteps<<"\n";

    std::cout << "\n" << "-----------------------------------------------------------\n";
    std::cout << "B: Higgs boson discovery\n";
    std::cout << "-----------------------------------------------------------\n\n";

    HiggsFit fit;

    fit.readData();

    Vector p(3);

    // Initial guesses
    p[0] = 125.0;      // mass
    p[1] = 2.0;        // width
    p[2] = 20.0;       // scale

    Vector result =
        newton(
            [&](const Vector& v)
            {
                return fit.deviation(v);
            },
            p,
            1e-3,
            steps
        );

    std::cout << "Best fit parameters\n\n";

    std::cout << "Mass   = " << result[0] << " GeV\n";
    std::cout << "Width  = " << result[1] << " GeV\n";
    std::cout << "Scale  = " << result[2] << "\n\n";

    std::cout << "Deviation = "
              << fit.deviation(result)
              << "\n";

    std::cout << "Steps = "
              << steps
              << "\n";

    fit.writeData("data.dat");
    fit.writeFit("fit.dat", result);

    std::cout << "\n";
    std::cout << "Created data.dat\n";
    std::cout << "Created fit.dat\n";

    std::cout << "\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "C: Central instead of forward finite difference approximation for the derivatives\n";
    std::cout << "-----------------------------------------------------------\n\n";

    Vector xc(2);

    xc[0] = -2;
    xc[1] = 5;

    Vector rc = newtonCentral(rosenbrock, xc, 1e-3, steps);

    int centralRosenSteps = steps;
    double centralRosenValue = rosenbrock(rc);

    std::cout << "Rosenbrock (central differences)\n";
    std::cout << rc << "\n";
    std::cout << "Function value = " << centralRosenValue << "\n";
    std::cout << "Steps = " << centralRosenSteps << "\n\n";

    xc[0] = 5;
    xc[1] = 5;

    Vector hc = newtonCentral(himmelblau, xc, 1e-3, steps);

    int centralHimmelSteps = steps;
    double centralHimmelValue = himmelblau(hc);

    std::cout << "Himmelblau (central differences)\n";
    std::cout << hc << "\n";
    std::cout << "Function value = " << centralHimmelValue << "\n";
    std::cout << "Steps = " << centralHimmelSteps << "\n";

    std::cout << "\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Comparison of forward and central finite differences\n";
    std::cout << "-----------------------------------------------------------\n\n";

    std::cout << "Rosenbrock:\n";
    std::cout << "  Forward differences:\n";
    std::cout << "    Function value = " << forwardRosenValue << "\n";
    std::cout << "    Steps          = " << forwardRosenSteps << "\n";

    std::cout << "  Central differences:\n";
    std::cout << "    Function value = " << centralRosenValue << "\n";
    std::cout << "    Steps          = " << centralRosenSteps << "\n\n";

    std::cout << "Himmelblau:\n";
    std::cout << "  Forward differences:\n";
    std::cout << "    Function value = " << forwardHimmelValue << "\n";
    std::cout << "    Steps          = " << forwardHimmelSteps << "\n";

    std::cout << "  Central differences:\n";
    std::cout << "    Function value = " << centralHimmelValue << "\n";
    std::cout << "    Steps          = " << centralHimmelSteps << "\n\n";

    std::cout << "Conclusion:\n";

    if (centralRosenSteps < forwardRosenSteps ||
        centralHimmelSteps < forwardHimmelSteps)
    {
        std::cout << "Central finite differences converged in fewer Newton iterations ";
        std::cout << "for one or more test functions and produced function values ";
        std::cout << "at least as accurate as the forward difference approximation.\n";
    }
    else
    {
        std::cout << "Both methods produced comparable results for these test problems.\n";
    }

    return 0;
}