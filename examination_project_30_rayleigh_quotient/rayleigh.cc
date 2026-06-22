#include "rayleigh.h"
#include "minimizer.h"

#include <cmath>

namespace
{

Eigenpair solveEigenpair(
    const Matrix& H,
    const Vector* orthogonalTo,
    double tolerance,
    int maxIterations)
{
    const int n = H.numRows();

    Vector v(n, 1.0);

    // Orthogonalize initial guess if requested
    if (orthogonalTo != nullptr)
    {
        double proj = dot(v, *orthogonalTo);

        for (int i = 0; i < n; i++)
            v[i] -= proj * (*orthogonalTo)[i];
    }

    normalize(v);

    double R = rayleighQuotient(H, v);

    for (int iter = 0; iter < maxIterations; iter++)
    {
        Vector Hv = H * v;

        //--------------------------------------------
        // Search direction
        //--------------------------------------------

        Vector delta(n);

        for (int i = 0; i < n; i++)
            delta[i] = Hv[i] - R * v[i];

        //--------------------------------------------
        // Precompute coefficients
        //--------------------------------------------

        Vector Hdelta = H * delta;

        double A = dot(v, Hv);
        double B = dot(delta, Hv);
        double C = dot(delta, Hdelta);
        double D = dot(v, v);
        double E = dot(delta, delta);

        auto f = [&](double alpha)
        {
            return (A - 2.0 * alpha * B + alpha * alpha * C)
                 / (D + alpha * alpha * E);
        };

        double alpha = goldenSectionSearch(f, 0.0, 2.0);

        //--------------------------------------------
        // Update
        //--------------------------------------------

        for (int i = 0; i < n; i++)
            v[i] -= alpha * delta[i];

        //--------------------------------------------
        // Keep orthogonal to first eigenvector
        //--------------------------------------------

        if (orthogonalTo != nullptr)
        {
            double proj = dot(v, *orthogonalTo);

            for (int i = 0; i < n; i++)
                v[i] -= proj * (*orthogonalTo)[i];
        }

        normalize(v);

        double newR = rayleighQuotient(H, v);

        //--------------------------------------------
        // Convergence test
        //--------------------------------------------

        if (std::abs(newR - R) < tolerance)
        {
            Eigenpair result;
            result.eigenvalue = newR;
            result.eigenvector = v;
            result.iterations = iter + 1;
            return result;
        }

        R = newR;
    }

    Eigenpair result;
    result.eigenvalue = R;
    result.eigenvector = v;
    result.iterations = maxIterations;

    return result;
}

} // anonymous namespace

//------------------------------------------------------------

double rayleighQuotient(const Matrix& H, const Vector& v)
{
    Vector Hv = H * v;
    return dot(v, Hv) / dot(v, v);
}

//------------------------------------------------------------

Eigenpair lowestEigenpair(
    const Matrix& H,
    double tolerance,
    int maxIterations)
{
    return solveEigenpair(H, nullptr, tolerance, maxIterations);
}

//------------------------------------------------------------

Eigenpair secondEigenpair(
    const Matrix& H,
    const Vector& firstEigenvector,
    double tolerance,
    int maxIterations)
{
    return solveEigenpair(
        H,
        &firstEigenvector,
        tolerance,
        maxIterations);
}