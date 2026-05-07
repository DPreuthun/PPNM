#include "ode.h"
#include <cmath>

std::tuple<vector,vector> rkstep12(
    std::function<vector(double,vector)> f,
    double x,
    vector y,
    double h
){
    vector k0 = f(x,y);

    vector k1 = f(x+h/2, y + k0*(h/2));

    vector yh = y + k1*h;

    vector err = (k1-k0)*h;

    return {yh, err};
}

std::tuple<std::vector<double>, std::vector<vector>> driver(
    std::function<vector(double,vector)> F,
    double a,
    double b,
    vector yinit,
    double h,
    double acc,
    double eps
){
    double x = a;
    vector y = yinit;

    std::vector<double> xlist;
    std::vector<vector> ylist;

    xlist.push_back(x);
    ylist.push_back(y);

    while(x < b){

        if(x+h > b)
            h = b-x;

        auto [yh, errvec] = rkstep12(F,x,y,h);

        double err = errvec.norm();

        double tol =
            (acc + eps*yh.norm())*std::sqrt(h/(b-a));

        if(err <= tol){
            x += h;
            y = yh;

            xlist.push_back(x);
            ylist.push_back(y);
        }

        if(err > 0)
            h *= std::min(std::pow(tol/err,0.25)*0.95,2.0);
        else
            h *= 2;
    }

    return {xlist,ylist};
}