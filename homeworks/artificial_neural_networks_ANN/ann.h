#ifndef ANN_H
#define ANN_H

#include <vector>
#include <functional>
#include "vector.h"

class ANN
{
private:

    int n;

public:

    // Total parameter vector:
    // p = [a0,b0,w0,a1,b1,w1,...]
    Vector p;

    // Activation function
    std::function<double(double)> f;

    ANN(int neurons);

    // Network response
    double response(double x) const;

    // Activation
    double activation(double x) const;

    // First derivative of activation
    double activationDerivative(double x) const;

    // Second derivative
    double activationSecondDerivative(double x) const;

    // Antiderivative
    double activationIntegral(double x) const;

    // Network derivatives
    double derivative(double x) const;

    double secondDerivative(double x) const;

    double integral(double x) const;

    // Parameter access

    double& a(int i);
    double& b(int i);
    double& w(int i);

    double a(int i) const;
    double b(int i) const;
    double w(int i) const;

    int neurons() const;

    // Training

    double cost(const std::vector<double>& xs,
                const std::vector<double>& ys) const;

    void train(const std::vector<double>& xs,
               const std::vector<double>& ys,
               int maxIterations = 5000,
               double learningRate = 0.01);

};

#endif