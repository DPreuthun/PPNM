#include "ann.h"

#include <cmath>
#include <iostream>

ANN::ANN(int neurons)
{
    n = neurons;

    p = Vector(3*n);

    // Gaussian wavelet
    f = [](double x)
    {
        return x*std::exp(-x*x);
    };

    for(int i=0;i<n;i++)
    {
        a(i) = -1.0 + 2.0*i/(n-1.0);
        b(i) = 0.5;
        w(i) = 1.0;
    }
}

double ANN::activation(double x) const
{
    return f(x);
}

double ANN::activationDerivative(double x) const
{
    return (1.0-2.0*x*x)*std::exp(-x*x);
}

double ANN::activationSecondDerivative(double x) const
{
    return (4*x*x*x-6*x)*std::exp(-x*x);
}

double ANN::activationIntegral(double x) const
{
    return -0.5*std::exp(-x*x);
}

double ANN::response(double x) const
{
    double sum = 0;

    for(int i=0;i<n;i++)
    {
        double z = (x-a(i))/b(i);

        sum += w(i)*activation(z);
    }

    return sum;
}

double ANN::derivative(double x) const
{
    double sum = 0;

    for(int i=0;i<n;i++)
    {
        double z = (x-a(i))/b(i);

        sum += w(i)*activationDerivative(z)/b(i);
    }

    return sum;
}

double ANN::secondDerivative(double x) const
{
    double sum = 0;

    for(int i=0;i<n;i++)
    {
        double z = (x-a(i))/b(i);

        sum += w(i)*activationSecondDerivative(z)/(b(i)*b(i));
    }

    return sum;
}

double ANN::integral(double x) const
{
    double sum = 0;

    for(int i=0;i<n;i++)
    {
        double z = (x-a(i))/b(i);

        sum += w(i)*b(i)*activationIntegral(z);
    }

    return sum;
}

double& ANN::a(int i)
{
    return p[3*i];
}

double& ANN::b(int i)
{
    return p[3*i+1];
}

double& ANN::w(int i)
{
    return p[3*i+2];
}

double ANN::a(int i) const
{
    return p[3*i];
}

double ANN::b(int i) const
{
    return p[3*i+1];
}

double ANN::w(int i) const
{
    return p[3*i+2];
}

int ANN::neurons() const
{
    return n;
}

double ANN::cost(const std::vector<double>& xs,
                 const std::vector<double>& ys) const
{
    double c = 0;

    for(size_t i=0;i<xs.size();i++)
    {
        double d = response(xs[i])-ys[i];

        c += d*d;
    }

    return c;
}

void ANN::train(const std::vector<double>& xs,
                const std::vector<double>& ys,
                int maxIterations,
                double learningRate)
{
    const double eps = 1e-6;

    for(int iter=0;iter<maxIterations;iter++)
    {
        Vector grad(3*n);

        double oldCost = cost(xs,ys);

        for(int i=0;i<3*n;i++)
        {
            p[i]+=eps;

            double c1 = cost(xs,ys);

            p[i]-=2*eps;

            double c2 = cost(xs,ys);

            p[i]+=eps;

            grad[i]=(c1-c2)/(2*eps);
        }

        for(int i=0;i<3*n;i++)
            p[i]-=learningRate*grad[i];

        double newCost = cost(xs,ys);

        if(iter % 500 == 0)
        {
            std::cout
                << "Iteration "
                << iter
                << "   Cost = "
                << newCost
                << "\n";
        }

        if(std::abs(oldCost-newCost)<1e-10)
        {
            std::cout
                << "Training converged after "
                << iter
                << " iterations.\n";

            std::cout
                << "Final cost = "
                << newCost
                << "\n";

            return;
        }
    }

    std::cout
    << "\nTraining finished.\n";

    std::cout
        << "Iterations = "
        << maxIterations
        << "\n";

    std::cout
        << "Final cost = "
        << cost(xs,ys)
        << "\n";
}