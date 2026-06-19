#include "higgs.h"

#include <iostream>
#include <cmath>
#include <fstream>

void HiggsFit::readData()
{
    energy.clear();
    signal.clear();
    error.clear();

    double E,s,e;

    while(std::cin >> E >> s >> e)
    {
        energy.push_back(E);
        signal.push_back(s);
        error.push_back(e);
    }
}

double HiggsFit::breitWigner(double E,
                             double m,
                             double gamma,
                             double A) const
{
    return A /
           ( (E-m)*(E-m)
           + gamma*gamma/4.0 );
}

double HiggsFit::deviation(const Vector& p) const
{
    double m     = p[0];
    double gamma = p[1];
    double A     = p[2];

    double sum = 0.0;

    for(size_t i=0;i<energy.size();i++)
    {
        double model =
            breitWigner(energy[i],m,gamma,A);

        double d =
            (model-signal[i])/error[i];

        sum += d*d;
    }

    return sum;
}

int HiggsFit::size() const
{
    return energy.size();
}

void HiggsFit::writeData(const std::string& filename) const
{
    std::ofstream out(filename);

    for(size_t i=0;i<energy.size();i++)
    {
        out << energy[i] << " "
            << signal[i] << " "
            << error[i] << "\n";
    }
}

void HiggsFit::writeFit(const std::string& filename,
                        const Vector& p) const
{
    std::ofstream out(filename);

    double m     = p[0];
    double gamma = p[1];
    double A     = p[2];

    double xmin = energy.front();
    double xmax = energy.back();

    int N = 500;

    for(int i=0;i<=N;i++)
    {
        double E = xmin + (xmax-xmin)*i/N;

        out << E << " "
            << breitWigner(E,m,gamma,A)
            << "\n";
    }
}