#include "matrix.h"

Matrix::Matrix(int r, int c)
    : rows(r), cols(c), data(r * c, 0.0)
{
}

double& Matrix::operator()(int i,int j){
    return data[i*cols+j];
}

double Matrix::operator()(int i,int j) const{
    return data[i*cols+j];
}

int Matrix::numRows() const{
    return rows;
}

int Matrix::numCols() const{
    return cols;
}

std::ostream& operator<<(std::ostream& os, const Matrix& M)
{
    for(int i=0;i<M.numRows();i++){
        for(int j=0;j<M.numCols();j++)
            os << M(i,j) << " ";
        os << '\n';
    }
    return os;
}