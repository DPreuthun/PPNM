#include<cmath>
#include<numbers>
#include"sfuns.h"
#include<limits>
namespace sfuns{
constexpr double PI = std::numbers::pi;
constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
double lngamma(double x){
	if(x <= 0) return NaN;
	if(x < 9) return lngamma(x+1) - std::log(x);
	double log_sqrt_2pi = 0.5 * std::log(2 * PI);
    return x*std::log(x) - x + log_sqrt_2pi
           + 1.0/(12*x) - 1.0/(360*x*x*x);
	}
}
