#include "newton.h"
#include "qr.h"
#include <cmath>
#include <iostream>

Vector gradient(std::function<double(const Vector&)> f, Vector x)
{
    double fx=f(x);

    Vector g(x.size());

    for(int i=0;i<x.size();i++){

        double dx=(1+std::abs(x[i]))*pow(2,-26);

        x[i]+=dx;

        g[i]=(f(x)-fx)/dx;

        x[i]-=dx;
    }

    return g;
}

Matrix hessian(std::function<double(const Vector&)> f, Vector x)
{
    int n=x.size();

    Matrix H(n,n);

    Vector g0=gradient(f,x);

    for(int j=0;j<n;j++){

        double dx=(1+std::abs(x[j]))*pow(2,-13);

        x[j]+=dx;

        Vector g1=gradient(f,x);

        for(int i=0;i<n;i++)
            H(i,j)=(g1[i]-g0[i])/dx;

        x[j]-=dx;
    }

    return H;
}

Matrix hessianCentral(std::function<double(const Vector&)> f, Vector x)
{
    int n = x.size();

    Matrix H(n,n);

    Vector g0 = gradientCentral(f,x);

    for(int j=0;j<n;j++)
    {
        double dx = (1 + std::abs(x[j])) * cbrt(pow(2.0,-52));

        x[j] += dx;
        Vector gp = gradientCentral(f,x);

        x[j] -= 2*dx;
        Vector gm = gradientCentral(f,x);

        x[j] += dx;

        for(int i=0;i<n;i++)
            H(i,j) = (gp[i]-gm[i])/(2*dx);
    }

    return H;
}

Vector gradientCentral(std::function<double(const Vector&)> f, Vector x)
{
    Vector g(x.size());

    for(int i=0;i<x.size();i++)
    {
        double dx = (1 + std::abs(x[i])) * cbrt(pow(2.0,-52));

        x[i] += dx;
        double fp = f(x);

        x[i] -= 2*dx;
        double fm = f(x);

        x[i] += dx;

        g[i] = (fp - fm)/(2*dx);
    }

    return g;
}

Vector newton(std::function<double(const Vector&)> f,
              Vector x,
              double acc,
              int& steps)
{
    steps=0;

    while(true){

        Vector g=gradient(f,x);

        if(g.norm()<acc)
            break;

        Matrix H=hessian(f,x);

        // Levenberg regularization
        for(int i=0;i<H.numRows();i++)
            H(i,i)+=1e-6;

        Vector minusG(g.size());

        for(int i=0;i<g.size();i++)
            minusG[i]=-g[i];

        QR qr(H);

        Vector dx=qr.solve(minusG);
        
        double fx = f(x);
        double lambda = 1.0;

        bool accepted = false;

        while(lambda >= 1.0/1024){

            Vector trial = x + dx*lambda;

            if(f(trial) < fx){
                x = trial;
                accepted = true;
                break;
            }

            lambda /= 2.0;
        }

        if(!accepted)
            break;

        if((dx * lambda).norm() < acc)
            break;

        steps++;

        if(steps >= 1000){
            std::cout << "Warning: maximum number of iterations reached.\n";
            break;
}
}

    return x;
}

Vector newtonCentral(std::function<double(const Vector&)> f,
              Vector x,
              double acc,
              int& steps)
{
    steps=0;

    while(true){

        Vector g = gradientCentral(f,x);

        if(g.norm()<acc)
            break;

        Matrix H = hessianCentral(f,x);

        // Levenberg regularization
        for(int i=0;i<H.numRows();i++)
            H(i,i)+=1e-6;

        Vector minusG(g.size());

        for(int i=0;i<g.size();i++)
            minusG[i]=-g[i];

        QR qr(H);

        Vector dx=qr.solve(minusG);
        
        double fx = f(x);
        double lambda = 1.0;

        bool accepted = false;

        while(lambda >= 1.0/1024){

            Vector trial = x + dx*lambda;

            if(f(trial) < fx){
                x = trial;
                accepted = true;
                break;
            }

            lambda /= 2.0;
        }

        if(!accepted)
            break;

        if((dx * lambda).norm() < acc)
            break;

        steps++;

        if(steps >= 1000){
            std::cout << "Warning: maximum number of iterations reached.\n";
            break;
}
}

    return x;
}