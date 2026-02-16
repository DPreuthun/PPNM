#include<iostream>
#include<cstdio>
#include"sfuns.h"
#include<cmath>
int main() {
	double x = 1;
	double y = sfuns::lngamma(x);
	std::cout << "lngamma(1) = " << y << "\n";
	for(double x = 1; x <= 9; x += 1){
		std::cout << "lngamma("<< x <<") = " << sfuns::lngamma(x) << " tgamma("<< x <<") = " << std::tgamma(x) << "\n";}
	return 0;
}
