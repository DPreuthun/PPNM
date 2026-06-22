#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "hydrogen.h"
#include "matrix.h"
#include "rayleigh.h"
#include "timer.h"

using std::cout;
using std::endl;
using std::ofstream;

int main()
{
    ofstream out("output.txt");

    if (!out)
    {
        std::cerr << "Could not open output.txt\n";
        return 1;
    }

    //--------------------------------------------------------
    // Test matrix
    //--------------------------------------------------------

    Matrix H(4,4);

    H(0,0)=4;  H(0,1)=1;  H(0,2)=0;  H(0,3)=0;
    H(1,0)=1;  H(1,1)=3;  H(1,2)=1;  H(1,3)=0;
    H(2,0)=0;  H(2,1)=1;  H(2,2)=2;  H(2,3)=1;
    H(3,0)=0;  H(3,1)=0;  H(3,2)=1;  H(3,3)=1;

    cout << "=========================================\n";
    cout << "Test matrix\n";
    cout << "=========================================\n";

    out << "=========================================\n";
    out << "Test matrix\n";
    out << "=========================================\n";

    Eigenpair ground = lowestEigenpair(H);

    cout << "Smallest eigenvalue : "
         << std::setprecision(12)
         << ground.eigenvalue << endl;

    cout << "Iterations          : "
         << ground.iterations << endl;

    out << "Smallest eigenvalue : "
        << std::setprecision(12)
        << ground.eigenvalue << endl;

    out << "Iterations          : "
        << ground.iterations << endl;

    //--------------------------------------------------------
    // Residual for smallest eigenpair
    //--------------------------------------------------------

    Vector Hv = H * ground.eigenvector;
    Vector residual(H.numRows());

    for (int i = 0; i < H.numRows(); i++)
    {
        residual[i] =
            Hv[i]
            - ground.eigenvalue * ground.eigenvector[i];
    }

    cout << "Residual norm       : "
        << norm(residual) << endl;

    out << "Residual norm       : "
        << norm(residual) << endl;

    cout << "Eigenvector         : ";

    out << "Eigenvector         : ";

    for (double x : ground.eigenvector)
    {
        cout << x << " ";
        out  << x << " ";
    }

    cout << '\n';
    out  << '\n';

    //--------------------------------------------------------

    Eigenpair excited =
        secondEigenpair(H, ground.eigenvector);

    cout << "\nSecond eigenvalue   : "
        << excited.eigenvalue << endl;

    cout << "Iterations          : "
        << excited.iterations << endl;

    cout << "Eigenvector         : ";

    for (double x : excited.eigenvector)
        cout << x << " ";

    cout << endl;

    out << "\nSecond eigenvalue   : "
        << excited.eigenvalue << endl;

    out << "Iterations          : "
        << excited.iterations << endl;

    out << "Eigenvector         : ";

    for (double x : excited.eigenvector)
        out << x << " ";

    out << endl;

    //--------------------------------------------------------
    // Hydrogen
    //--------------------------------------------------------

    cout << "\n=========================================\n";
    cout << "Hydrogen atom\n";
    cout << "=========================================\n";

    out << "\n=========================================\n";
    out << "Hydrogen atom\n";
    out << "=========================================\n";

    Matrix hydrogen = hydrogenHamiltonian(300,20.0);

    Eigenpair hydrogenGround = lowestEigenpair(hydrogen);

    Vector HvHydrogen = hydrogen * hydrogenGround.eigenvector;
    Vector residualHydrogen(hydrogen.numRows());

    for(int i=0;i<hydrogen.numRows();i++)
    {
        residualHydrogen[i]=
            HvHydrogen[i]
            - hydrogenGround.eigenvalue*hydrogenGround.eigenvector[i];
    }

    double exact = -0.5;

    cout << "Hydrogen grid size  : "
        << hydrogen.numRows() << '\n';

    out << "Hydrogen grid size  : "
        << hydrogen.numRows() << '\n';

    cout << "Computed energy     : "
        << hydrogenGround.eigenvalue << '\n';

    cout << "Exact energy        : "
        << exact << '\n';

    cout << "Absolute error      : "
        << std::abs(hydrogenGround.eigenvalue - exact) << '\n';

    cout << "Residual norm       : "
        << norm(residualHydrogen) << '\n';

    out << "Computed energy     : "
        << hydrogenGround.eigenvalue << '\n';

    out << "Exact energy        : "
        << exact << '\n';

    out << "Absolute error      : "
        << std::abs(hydrogenGround.eigenvalue - exact) << '\n';

    out << "Residual norm       : "
        << norm(residualHydrogen) << '\n';

    //--------------------------------------------------------
    // Timing study
    //--------------------------------------------------------

    cout << "\n=========================================\n";
    cout << "Timing study\n";
    cout << "=========================================\n";

    out << "\n=========================================\n";
    out << "Timing study\n";
    out << "=========================================\n";

    ofstream timing("timing.dat");

    timing << "# MatrixSize AverageTime(s) AverageIterations\n";

    Timer timer;

    const int samples = 10;

for (int N = 50; N <= 1000; N += 50)
    {
        double totalTime = 0.0;
        double totalIterations = 0.0;

        for (int s = 0; s < samples; s++)
        {
            Matrix A = testMatrix(N);

            timer.start();

            Eigenpair result = lowestEigenpair(A);

            totalTime += timer.stop();
            totalIterations += result.iterations;
        }

        double averageTime = totalTime / samples;
        double averageIterations = totalIterations / samples;

        timing
            << N << " "
            << averageTime << " "
            << averageIterations << "\n";

        cout
            << "N = "
            << std::setw(4)
            << N
            << "   Avg Time = "
            << std::setw(10)
            << averageTime
            << " s   Avg Iter = "
            << averageIterations
            << endl;

        out
            << "N = "
            << std::setw(4)
            << N
            << "   Avg Time = "
            << std::setw(10)
            << averageTime
            << " s   Avg Iter = "
            << averageIterations
            << endl;
    }

    timing.close();

    //--------------------------------------------------------
    // Gnuplot script
    //--------------------------------------------------------

    ofstream gp("plot.gnu");

    gp << "set terminal pngcairo size 900,600\n";
    gp << "set output 'timing.png'\n";

    gp << "set grid\n";
    gp << "set key top left\n";

    gp << "set xlabel 'Matrix size N'\n";
    gp << "set ylabel 'Average runtime (s)'\n";
    gp << "set title 'Time scaling of Rayleigh quotient minimization'\n";

    gp << "set xtics 100\n";
    gp << "set format y '%.2f'\n";

    gp << "plot 'timing.dat' using 1:2 "
        "with linespoints lw 2 pt 7 "
        "title 'Measured runtime'\n";

    gp.close();

    //--------------------------------------------------------
    // Run gnuplot automatically
    //--------------------------------------------------------

    int status = std::system("gnuplot plot.gnu");

    if (status != 0)
    {
        std::cerr << "Warning: gnuplot could not be executed.\n";
    }

    cout << "\nTiming plot written to timing.png\n";
    out << "\nTiming plot written to timing.png\n";

    out.close();

    return 0;
}