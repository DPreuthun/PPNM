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

    // ---------- Read command line arguments ----------
    double rmax = 10.0;
    double dr   = 0.3;

    for(int i=1;i<argc;i++){
        std::string arg = argv[i];
        if(arg=="-rmax") rmax = atof(argv[++i]);
        if(arg=="-dr")   dr   = atof(argv[++i]);
    }

    // ---------- Build grid ----------
    int npoints = (int)(rmax/dr) - 1;

    pp::vector r(npoints);

    for(int i=0;i<npoints;i++)
        r[i] = dr*(i+1);

    // ---------- Build Hamiltonian ----------
    pp::matrix H(npoints,npoints);
    for(int i=0;i<npoints;i++)
    for(int j=0;j<npoints;j++)
        H(i,j)=0;

    for(int i=0;i<npoints-1;i++){
        H(i,i)   = -2*(-0.5/dr/dr);
        H(i,i+1) =  1*(-0.5/dr/dr);
        H(i+1,i) =  1*(-0.5/dr/dr);
    }

    H(npoints-1,npoints-1) = -2*(-0.5/dr/dr);

    for(int i=0;i<npoints;i++)
        H(i,i) += -1.0/r[i];

    // ---------- Diagonalize ----------
    pp::matrix Vh(npoints,npoints);
    pp::jacobi(H,Vh);

    // ---------- Find 3 lowest eigenvalues ----------
    int i1=0,i2=0,i3=0;
    double e1=1e100,e2=1e100,e3=1e100;

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
            e3=e; i3=i;
        }
    }

    std::cout << "\nThree lowest eigenvalues:\n";
    std::cout << "E1 = " << e1 << "\n";
    std::cout << "E2 = " << e2 << "\n";
    std::cout << "E3 = " << e3 << "\n";

    std::cout << "\nExact values:\n";
    std::cout << "-0.5\n";
    std::cout << "-0.125\n";
    std::cout << "-0.0555556\n";

    // ---------- Normalize eigenfunctions ----------
    double norm = 1.0/std::sqrt(dr);

    pp::vector psi1(npoints);
    pp::vector psi2(npoints);
    pp::vector psi3(npoints);

    for(int i=0;i<npoints;i++){
        psi1[i] = norm * Vh(i,i1);
        psi2[i] = norm * Vh(i,i2);
        psi3[i] = norm * Vh(i,i3);
    }

    // ---------- Write wavefunctions ----------
    std::ofstream wf("wavefunctions.dat");

    for(int i=0;i<npoints;i++){
        wf << r[i] << " "
           << psi1[i] << " "
           << psi2[i] << " "
           << psi3[i] << "\n";
    }

    wf.close();

    // ---------- Convergence vs dr ----------
    std::ofstream drfile("dr_convergence.dat");

    for(double dr_test=0.6; dr_test>=0.1; dr_test-=0.05){

        int n = (int)(rmax/dr_test) - 1;

        if(n < 3) continue;

        pp::vector r2(n);
        for(int i=0;i<n;i++)
            r2[i] = dr_test*(i+1);

        pp::matrix H2(n,n);
        for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            H2(i,j)=0;

        for(int i=0;i<n-1;i++){
            H2(i,i)   = -2*(-0.5/dr_test/dr_test);
            H2(i,i+1) =  1*(-0.5/dr_test/dr_test);
            H2(i+1,i) =  1*(-0.5/dr_test/dr_test);
        }

        H2(n-1,n-1) = -2*(-0.5/dr_test/dr_test);

        for(int i=0;i<n;i++)
            H2(i,i) += -1.0/r2[i];

        pp::matrix V2(n,n);
        pp::jacobi(H2,V2);

        double Emin = H2(0,0);

        for(int i=1;i<n;i++)
            if(H2(i,i) < Emin)
                Emin = H2(i,i);

        drfile << dr_test << " " << Emin << "\n";
    }

    drfile.close();

    // ---------- Convergence vs rmax ----------
    std::ofstream rmaxfile("rmax_convergence.dat");

    for(double r_test=5; r_test<=20; r_test+=1){

        int n = (int)(r_test/dr) - 1;

        if(n < 3) continue;

        pp::vector r2(n);
        for(int i=0;i<n;i++)
            r2[i] = dr*(i+1);

        pp::matrix H2(n,n);
        for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            H2(i,j)=0;

        for(int i=0;i<n-1;i++){
            H2(i,i)   = -2*(-0.5/dr/dr);
            H2(i,i+1) =  1*(-0.5/dr/dr);
            H2(i+1,i) =  1*(-0.5/dr/dr);
        }

        H2(n-1,n-1) = -2*(-0.5/dr/dr);

        for(int i=0;i<n;i++)
            H2(i,i) += -1.0/r2[i];

        pp::matrix V2(n,n);
        pp::jacobi(H2,V2);

        double Emin = H2(0,0);

        for(int i=1;i<n;i++)
            if(H2(i,i) < Emin)
                Emin = H2(i,i);

        rmaxfile << r_test << " " << Emin << "\n";
    }

    rmaxfile.close();
    
    return 0;
}