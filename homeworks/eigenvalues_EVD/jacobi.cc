#include "jacobi.h"
#include <cmath>

namespace pp {

void timesJ(matrix& A, int p, int q, double theta) {
    double c = cos(theta);
    double s = sin(theta);

    int n = A.row_count();

    for(int i = 0; i < n; i++) {
        double aip = A(i,p);
        double aiq = A(i,q);

        A(i,p) = c*aip - s*aiq;
        A(i,q) = s*aip + c*aiq;
    }
}

void Jtimes(matrix& A, int p, int q, double theta) {
    double c = cos(theta);
    double s = sin(theta);

    int n = A.col_count();

    for(int j = 0; j < n; j++) {
        double apj = A(p,j);
        double aqj = A(q,j);

        A(p,j) = c*apj + s*aqj;
        A(q,j) = -s*apj + c*aqj;
    }
}

int jacobi(matrix& A, matrix& V){

    int n = A.row_count();
    int rotations = 0;

    // initialize eigenvector matrix
    V = matrix(n,n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            V(i,j) = (i==j);

    while(true){

        int p=0,q=1;
        double max=0;

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                double val = fabs(A(i,j));
                if(val>max){
                    max=val;
                    p=i;
                    q=j;
                }
            }
        }

        if(max < 1e-10) break;

        double theta = 0.5 * atan2(2*A(p,q), A(q,q)-A(p,p));

        timesJ(A,p,q,theta);
        Jtimes(A,p,q,-theta);

        timesJ(V,p,q,theta);

        rotations++;
    }

    return rotations;
}

}