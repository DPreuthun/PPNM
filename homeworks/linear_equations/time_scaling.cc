#include "vecmatrix.h"
#include "qr.h"
#include <string>

int main(int argc, char* argv[]) {

    int N = 100;  // default

    // Read -size N from command line
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-size" && i + 1 < argc) {
            N = std::stoi(argv[i + 1]);
        }
    }

    // Generate random NxN matrix
    pp::matrix A = pp::random_int_matrix(N, N, 1, 10);

    pp::QR qr(A);

    return 0;
}