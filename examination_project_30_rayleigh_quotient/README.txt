========== Description ==========

This project implements a numerical method for solving symmetric eigenvalue problems by minimizing the Rayleigh quotient. 
The core of the implementation is an iterative Rayleigh quotient minimization algorithm. Starting from an initial normalized vector, the Rayleigh quotient and its analytical gradient are evaluated. 
The search direction is computed as Δv=(H−R)v, corresponding to the analytical gradient of the Rayleigh quotient, while the optimal step length is determined using a custom one-dimensional numerical line search.
After each iteration the vector is normalized to ensure numerical stability, and the process continues until convergence. 
The resulting vector represents the eigenvector, while the Rayleigh quotient gives the corresponding eigenvalue.

The algorithm is first tested on a small symmetric matrix, where both the smallest and second smallest eigenvalues are computed. 
The second eigenvalue is obtained by enforcing orthogonality to the first eigenvector. Residual norms are also calculated to verify the computed solutions.

The method is then applied to the radial Schrödinger equation for the hydrogen atom. 
Using a finite-difference discretization, the Hamiltonian is represented as a symmetric matrix, and the ground-state energy is computed and compared with the exact analytical value of (-0.5) Hartree.

Finally, the computational performance of the implementation is investigated by measuring the average runtime for increasing matrix sizes. 
The timing data are written to a file and automatically plotted using gnuplot, providing an overview of the scaling behaviour of the implemented algorithm. 
Based on these measurements, matrices of size up to approximately 9000 × 9000 can be solved within about 2 seconds on the test machine, giving a practical upper limit for this implementation.


========== Self-evaluation ==========

9/10

The project meets the requirements of the assignment and produces accurate results. The implementation is modular and well-structured, with only minor room for improvement in optimization and numerical accuracy.


========== To run the program ==========

In terminal do: "make clean" ---> "make run"


========== To view results ==========

The results are then printed to "output.txt" and will also be printed in terminal when doing "make run" in terminal.

See "timing.png" to inspect the time scaling plot.


========== AI usage ==========

ChatGPT was used as a programming assistant during the development of the project. 
It was used to discuss the numerical method, suggest code structure, and assist in implementing and debugging the C++ source files, including the Makefile.