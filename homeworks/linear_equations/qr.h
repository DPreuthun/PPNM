#ifndef QR_H
#define QR_H

#include "vecmatrix.h"

namespace pp {

class QR {
private:
    matrix Q;
    matrix R;

public:
    QR(const matrix& A);

    vector solve(const vector& b) const;
    double det() const;
    matrix inverse() const;

    matrix getQ() const { return Q; }
    matrix getR() const { return R; }
};

// Output operator for vector
std::ostream& operator<<(std::ostream& os, const vector& v);

// Output operator for matrix
std::ostream& operator<<(std::ostream& os, const matrix& M);

}

#endif