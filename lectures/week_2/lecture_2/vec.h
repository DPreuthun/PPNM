#pragma once
#include<string>
#include<iostream>
#include<cstdio>
namespace pp{
    struct vec{
        double x,y,z;

        // constructors
        vec(double a, double b, double c){ // parametrized constructor
            printf("parametrized constructor called...\n");
            x=a; y=b; z=c;
        }
        
        vec() : vec(0,0,0) {
            printf("default constructor called...\n");
        } // default constructor

        vec(const vec&)=default; // copy constructor vec a=b;
        vec(vec&&)=default; // move constructor vec a=b+c;

        // destructor
        ~vec(){
            printf("destructor called...\n");
        }

        // assignments
        vec& operator=(const vec&); // copy a=b;
        vec& operator=(vec&&); // move a=b+c;

        // member operators
        vec& operator*=(double);
        vec& operator/=(double);
        vec& operator+=(double);
        vec& operator-=(double);

        void print(const std::string& s="");

        // stream output
        friend std::ostream& operator<<(std::ostream&, const vec&);
    };
    // non-members
    vec operator-(const vec&);
    vec operator+(const vec&, const vec&);
    vec operator-(const vec&, const vec&);
    vec operator*(const vec&, double);
    vec operator*(double, const vec&);
    vec operator/(const vec&, double);
}