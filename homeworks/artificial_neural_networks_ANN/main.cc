#include <iostream>
#include <fstream>
#include <vector>

#include "ann.h"
#include "functions.h"
#include <iomanip>

int main()
{
    std::cout << "\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "PART A\n";
    std::cout << "-----------------------------------------------------------\n\n";

    std::vector<double> xs;
    std::vector<double> ys;

    // Sample target function
    for(double x=-1.0;x<=1.0001;x+=0.1)
    {
        xs.push_back(x);
        ys.push_back(targetFunction(x));
    }

    ANN network(8);

    std::cout << "Target function:\n";
    std::cout << "g(x)=cos(5*x-1)*exp(-x*x)\n\n";

    std::cout << "Hidden neurons : "
              << network.neurons()
              << "\n\n";

    std::cout << "Training network...\n\n";

    network.train(xs,ys);

    std::cout << "\n";

    std::cout
        << "-------------------------------------------------------------\n";

    std::cout
        << "x\tTarget\t\tANN\n";

    std::cout
        << "-------------------------------------------------------------\n";

    for(double x=-1.0;x<=1.0001;x+=0.1)
    {
        std::cout
            << x
            << "\t"
            << targetFunction(x)
            << "\t"
            << network.response(x)
            << "\n";
    }

    std::ofstream data("data.dat");

    for(double x=-1.0;x<=1.0001;x+=0.1)
    {
        data
            << x
            << " "
            << targetFunction(x)
            << "\n";
    }

    data.close();

    std::ofstream fit("fit.dat");

    for(double x=-1.0;x<=1.0001;x+=0.01)
    {
        fit
            << x
            << " "
            << network.response(x)
            << "\n";
    }

    fit.close();

    std::cout << "\n";
    std::cout << "Created data.dat\n";
    std::cout << "Created fit.dat\n";

    std::cout << "\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "PART B\n";
    std::cout << "-----------------------------------------------------------\n\n";

    std::ofstream derivatives("derivatives.dat");

    for(double x=-1.0;x<=1.0001;x+=0.01)
    {
        derivatives
            << x << " "
            << network.response(x) << " "
            << network.derivative(x) << " "
            << network.secondDerivative(x) << " "
            << network.integral(x)
            << "\n";
    }

    derivatives.close();

    std::cout
    << std::left
    << std::setw(8)  << "x"
    << std::setw(15) << "Exact f"
    << std::setw(15) << "ANN f"
    << std::setw(15) << "Exact f'"
    << std::setw(15) << "ANN f'"
    << "\n";

    std::cout
    << "--------------------------------------------------------------------------\n";

    for(double x=-1.0;x<=1.0001;x+=0.2)
    {
        std::cout
        << std::left
        << std::setw(8)  << x
        << std::setw(15) << targetFunction(x)
        << std::setw(15) << network.response(x)
        << std::setw(15) << targetDerivative(x)
        << std::setw(15) << network.derivative(x)
        << "\n";
    }

    std::cout << "\nSecond derivative comparison\n\n";

    std::cout
    << std::left
    << std::setw(8)  << "x"
    << std::setw(15) << "Exact f''"
    << std::setw(15) << "ANN f''"
    << "\n";

    std::cout
    << "----------------------------------------\n";

    for(double x=-1.0;x<=1.0001;x+=0.2)
    {
        std::cout
        << std::left
        << std::setw(8)  << x
        << std::setw(15) << targetSecondDerivative(x)
        << std::setw(15) << network.secondDerivative(x)
        << "\n";
    }

    return 0;
}