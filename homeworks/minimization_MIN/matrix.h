#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

#include <vector>

class Matrix{
private:
    int rows,cols;
    std::vector<double> data;

public:
    Matrix(int r=0,int c=0);

    double& operator()(int i,int j);
    double operator()(int i,int j) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& M);

    int numRows() const;
    int numCols() const;
};

#endif