#include<iostream>
#include<cstdio>
#include<vector>
#include"hello.h"
#include"vec.h"
int main(){
    hello();
    double a=1.0;
    double b=a;
    if (a==b) std::cout << "a is equal to b\n";
    else std::cout << "a is not equal to b\n";
    std::vector<double> v {1, 2, 3};
    for(size_t i=0; i<v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << "\n";
    for(auto vi : v)
        std::cout << vi << " ";
    std::cout << "\n";
    for(auto& vi : v) vi=6;
    for(auto vi : v) 
        std::cout << vi << " ";
    std::cout << "\n";
    //auto u=v;
    //auto& w=v;

    pp::vec vectest {1, 2, 3};
    vectest.x=6;
    std::cout << vectest.x << " " << vectest.y << " " << vectest.z << "\n";
return 0;
}