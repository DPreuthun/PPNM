#include "vecmatrix.h"
#include "jacobi.h"
#include <iostream>
#include <chrono>

int main(){

    std::cout << "# n time\n";

    for(int n=50; n<=150; n+=10){

        pp::matrix A = pp::random_int_matrix(n,n,1,10);
        A.make_symmetric();

        pp::matrix V(n,n);

        auto start = std::chrono::high_resolution_clock::now();

        pp::jacobi(A,V);

        auto end = std::chrono::high_resolution_clock::now();

        double time = std::chrono::duration<double>(end-start).count();

        std::cout << n << " " << time << "\n";
    }
}