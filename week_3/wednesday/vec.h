#pragma once
#include<string>
#include<iostream>
#include<cstdio>
#include <complex>
#include <type_traits>

// Make sure only numbers are valid check that T is a number and if it does +, -, * and / (to include complex)
template<typename T>
concept Arithmetic =
    std::is_arithmetic_v<T> ||
    requires(T a) {
        a + a;
        a - a;
        a * a;
        a / a;
    };

namespace pp {

template<Arithmetic T>
struct vec;

template<Arithmetic T>
std::ostream& operator<<(std::ostream&, const vec<T>&);

template<Arithmetic T>
struct vec {
    T x,y,z;
        // constructors
        vec(T a, T b, T c){ // parametrized constructor
            printf("parametrized constructor called...\n");
            x=a; y=b; z=c;
        }
        
        vec() : vec(T{},T{},T{}) {
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
        vec& operator*=(T);
        vec& operator/=(T);
        vec& operator+=(T);
        vec& operator-=(T);

        void print(const std::string& s="");

        // stream output
        friend std::ostream& operator<< <>(std::ostream&, const vec&);
    };
    // non-members
    template<Arithmetic T>
    vec<T> operator-(const vec<T>&);

    template<Arithmetic T>
    vec<T> operator+(const vec<T>&, const vec<T>&);

    template<Arithmetic T>
    vec<T> operator-(const vec<T>&, const vec<T>&);

    template<Arithmetic T>
    vec<T> operator*(const vec<T>&, const T&);

    template<Arithmetic T>
    vec<T> operator*(const T&, const vec<T>&);

    template<Arithmetic T>
    vec<T> operator/(const vec<T>&, const T&);

    
};

// ===== OPERATOR IMPLEMENTATIONS =====

template<Arithmetic T>
std::ostream& pp::operator<<(std::ostream& os, const vec<T>& v){
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

template<Arithmetic T>
pp::vec<T> pp::operator+(const vec<T>& a, const vec<T>& b){
    return vec<T>(a.x + b.x,
                  a.y + b.y,
                  a.z + b.z);
}

template<Arithmetic T>
pp::vec<T> pp::operator-(const vec<T>& a, const vec<T>& b){
    return vec<T>(a.x - b.x,
                  a.y - b.y,
                  a.z - b.z);
}

template<Arithmetic T>
pp::vec<T> pp::operator-(const vec<T>& v){
    return vec<T>(-v.x, -v.y, -v.z);
}

template<Arithmetic T>
pp::vec<T> pp::operator*(const vec<T>& v, const T& s){
    return vec<T>(v.x * s,
                  v.y * s,
                  v.z * s);
}

template<Arithmetic T>
pp::vec<T> pp::operator*(const T& s, const vec<T>& v){
    return v * s;
}

template<Arithmetic T>
pp::vec<T> pp::operator/(const vec<T>& v, const T& s){
    return vec<T>(v.x / s,
                  v.y / s,
                  v.z / s);
}