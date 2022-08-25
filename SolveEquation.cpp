#include "math.h"
#include "assert.h"
#include "stdio.h"
#include "SolveEquation.h"

const double epsilon = 10e-8; // The smallest possible positive value of a double variable

void inputCoefficients(double *a, double *b, double *c) {
    printf("%s", "Enter coefficients: a b c\n");
    if (scanf("%lg %lg %lg", a, b, c) < 3)
    {
        printf("%s\n", "Error: the format does not match the sample");
    }
}

NumberOfRoots_t solveSquare(double a, double b, double c, double *x1, double *x2) {
    assert(std::isfinite(a) && std::isfinite(b) && std::isfinite(c));
    assert(x2 != NULL && x1 != NULL);
    assert(x1 != x2);

    if (a == 0)
    {
        return solveLinear(b, c, x1);
    }

    double D = discriminant(a, b, c);
    if (D < -epsilon)
    {
        return NO_ROOTS;
    }

    if (areEqual(D, 0))
    {
        *x1 = -b / (2 * a);
        if (areEqual(*x1, 0))
            *x1 = 0;
        return ONE_ROOT;
    }

    *x1 = (-b - sqrt(D)) / (2 * a);
    if (areEqual(*x1, 0))
        *x1 = 0;
    *x2 = (-b + sqrt(D)) / (2 * a);
    if (areEqual(*x2, 0))
        *x2 = 0;
    return TWO_ROOTS;
}


NumberOfRoots_t solveLinear(double a, double b, double *ans) {
    assert(std::isfinite(a) && std::isfinite(b));
    assert(ans != NULL);

    if (a == 0)
    {
        return (b == 0) ? INF_ROOTS : NO_ROOTS;
    }

    *ans = -b / a;
    if (areEqual(*ans, 0))
        *ans = 0;
    return ONE_ROOT;
}

double discriminant(double a, double b, double c) {
    assert(std::isfinite(a) && std::isfinite(b) && std::isfinite(c));
    return (b * b - 4 * a * c);
}

void printAnswer(NumberOfRoots_t nRoots, double root1, double root2) {
    switch (nRoots)
    {
        case NO_ROOTS:
            printf("No solutions");
            break;
        case ONE_ROOT:
            printf("x = %lg", root1);
            break;
        case TWO_ROOTS:
            printf("x1 = %lg, x2 = %lg", root1, root2);
            break;
        case INF_ROOTS:
            printf("Any value");
            break;
        default:
            printf("Unreachable");
    }
}

void sPrintAnswer(char *target, NumberOfRoots_t nRoots, double root1, double root2) {
    switch (nRoots)
    {
        case NO_ROOTS:
            sprintf(target, "No solutions");
            break;
        case ONE_ROOT:
            sprintf(target, "x = %lg", root1);
            break;
        case TWO_ROOTS:
            sprintf(target, "x1 = %lg, x2 = %lg", root1, root2);
            break;
        case INF_ROOTS:
            sprintf(target, "Any value");
            break;
        default:
            sprintf(target, "Unreachable");
    }
}

bool areEqual(double a, double b) {
    if (abs(a-b) < epsilon)
    {
        return true;
    }
    return false;
}