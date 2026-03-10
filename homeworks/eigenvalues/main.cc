#include "vecmatrix.h"
#include "jacobi.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

int main(int argc,char** argv) {
    std::cout << std::fixed << std::setprecision(6);

    // A1
    pp::matrix A1 = pp::random_int_matrix(4,4,1,10);

    std::cout << "----------A1----------" << "\n";

    std::cout << "A = " << "\n" << A1 << "\n";

    pp::matrix AJ = A1;

    pp::timesJ(AJ, 0, 1, M_PI/4.0);

    std::cout << "A * J = " << "\n" << AJ << "\n";

    // A2
    pp::matrix A2 = pp::random_int_matrix(4,4,1,10);

    std::cout << "----------A2----------" << "\n";

    std::cout << "A = " << "\n" << A2 << "\n";

    pp::matrix JA = A2;

    pp::timesJ(JA, 0, 1, M_PI/4.0);

    std::cout << "J * A = " << "\n" << JA << "\n";

    // A3
    std::cout << "----------A3----------" << "\n";

    pp::matrix A3 = pp::random_int_matrix(4,4,1,10);

    A3.make_symmetric();

    pp::matrix A3_original = A3;

    std::cout << "A_sym = " << "\n" << A3 << "\n";

    pp::matrix V(4,4);
    
    pp::jacobi(A3,V);

    pp::matrix D = A3;

    std::cout << "D = " << "\n" << D << "\n";

    std::cout << "V = " << "\n" << V << "\n";

    std::cout << "V^T * A * V = " << "\n" << V.transpose() * A3_original * V << "\n";

    std::cout << "V * D * V^T = " << "\n" << V * D * V.transpose() << "\n";

    std::cout << "V^T * V = " << "\n" << V.transpose() * V << "\n";

    std::cout << "V * V^T = " << "\n" << V * V.transpose() << "\n";

    // B
    std::cout << "----------B----------" << "\n";

    double rmax = 10;
    double dr = 0.3;

    for(int i=1;i<argc;i++){
        std::string arg = argv[i];

        if(arg=="-rmax") rmax = atof(argv[++i]);
        if(arg=="-dr")   dr   = atof(argv[++i]);
    }

    int npoints = (int)(rmax/dr) - 1;

    pp::vector r(npoints);

    for(int i=0;i<npoints;i++)
        r[i] = dr*(i+1);
    
    pp::matrix H(npoints,npoints);

    for(int i=0;i<npoints-1;i++){

        H(i,i)   = -2*(-0.5/dr/dr);

        H(i,i+1) =  1*(-0.5/dr/dr);

        H(i+1,i) =  1*(-0.5/dr/dr);
    }

    H(npoints-1,npoints-1) = -2*(-0.5/dr/dr);

    for(int i=0;i<npoints;i++)
    H(i,i) += -1.0/r[i];

    pp::matrix Vh(npoints,npoints);

    pp::jacobi(H,Vh);

    double Emin = H(0,0);
    int index = 0;

    for(int i=1;i<npoints;i++){
        if(H(i,i) < Emin){
            Emin = H(i,i);
            index = i;
        }
    }

    pp::vector psi(npoints);

    int i1=0, i2=0, i3=0;
    double e1=1e100, e2=1e100, e3=1e100;

    for(int i=0;i<npoints;i++){
        double e = H(i,i);

        if(e < e1){
            e3=e2; i3=i2;
            e2=e1; i2=i1;
            e1=e;  i1=i;
        }
        else if(e < e2){
            e3=e2; i3=i2;
            e2=e;  i2=i;
        }
        else if(e < e3){
            e3=e;  i3=i;
        }
    }

    std::cout << "\nThree lowest eigenvalues:\n";
    std::cout << "E1 = " << e1 << "\n";
    std::cout << "E2 = " << e2 << "\n";
    std::cout << "E3 = " << e3 << "\n";

    std::cout << "\nFirst 10 components of the corresponding eigenvectors:\n";

    for(int i=0;i<10 && i<npoints;i++){
        std::cout << "i=" << i
                << "  psi1=" << Vh(i,i1)
                << "  psi2=" << Vh(i,i2)
                << "  psi3=" << Vh(i,i3)
                << "\n";
    }

    std::cout << "\nExact ground state energy = -0.5\n";
    
    return 0;
}