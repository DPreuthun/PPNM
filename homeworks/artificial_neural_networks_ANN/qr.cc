#include "qr.h"
#include <cmath>

QR::QR(const Matrix& A)
{
    int m = A.numRows();
    int n = A.numCols();

    Q = Matrix(m,n);
    R = Matrix(n,n);

    for(int j=0;j<n;j++){

        // Copy column j
        for(int i=0;i<m;i++)
            Q(i,j)=A(i,j);

        // Orthogonalization
        for(int k=0;k<j;k++){

            double dot=0;

            for(int i=0;i<m;i++)
                dot += Q(i,k)*Q(i,j);

            R(k,j)=dot;

            for(int i=0;i<m;i++)
                Q(i,j)-=dot*Q(i,k);
        }

        double norm=0;

        for(int i=0;i<m;i++)
            norm += Q(i,j)*Q(i,j);

        norm = std::sqrt(norm);

        R(j,j)=norm;

        for(int i=0;i<m;i++)
            Q(i,j)/=norm;
    }
}

Vector QR::solve(const Vector& b)
{
    int n = R.numCols();

    Vector y(n);

    // y = Qᵀb
    for(int i=0;i<n;i++){

        y[i]=0;

        for(int j=0;j<n;j++)
            y[i]+=Q(j,i)*b[j];
    }

    Vector x(n);

    // Back substitution
    for(int i=n-1;i>=0;i--){

        double sum=y[i];

        for(int j=i+1;j<n;j++)
            sum-=R(i,j)*x[j];

        x[i]=sum/R(i,i);
    }

    return x;
}