#ifndef QR_H
#define QR_H

#include "matrix.h"
#include "vector.h"

class QR {
private:
    Matrix Q;
    Matrix R;

public:
    QR(const Matrix& A);

    Vector solve(const Vector& b);
};

#endif