#include "jacobi.h"
#include <cmath>

namespace pp {

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

        // find largest off-diagonal element
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                double val = fabs(A(i,j));
                if(val > max){
                    max = val;
                    p = i;
                    q = j;
                }
            }
        }

        if(max < 1e-10) break;

        double theta = 0.5 * atan2(2*A(p,q), A(q,q)-A(p,p));
        double c = cos(theta);
        double s = sin(theta);

        double app = A(p,p);
        double aqq = A(q,q);
        double apq = A(p,q);

        // update diagonal elements
        A(p,p) = c*c*app - 2*s*c*apq + s*s*aqq;
        A(q,q) = s*s*app + 2*s*c*apq + c*c*aqq;
        A(p,q) = 0;
        A(q,p) = 0;

        // update remaining matrix elements (only symmetric parts)
        for(int i=0;i<n;i++){

            if(i!=p && i!=q){

                double aip = (i<p) ? A(i,p) : A(p,i);
                double aiq = (i<q) ? A(i,q) : A(q,i);

                double new_ip = c*aip - s*aiq;
                double new_iq = c*aiq + s*aip;

                if(i<p) A(i,p) = new_ip;
                else    A(p,i) = new_ip;

                if(i<q) A(i,q) = new_iq;
                else    A(q,i) = new_iq;
            }
        }

        // update eigenvectors
        for(int i=0;i<n;i++){
            double vip = V(i,p);
            double viq = V(i,q);

            V(i,p) = c*vip - s*viq;
            V(i,q) = s*vip + c*viq;
        }

        rotations++;
    }

    return rotations;
}

}