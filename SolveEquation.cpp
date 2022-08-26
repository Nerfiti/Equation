#include "math.h"
#include "assert.h"
#include "stdio.h"
#include "SolveEquation.h"

/// The smallest possible positive value of a double variable
const double epsilon = 10e-8;

void inputCoefficients(double *a, double *b, double *c)
{
    assert(a != NULL && b != NULL && c != NULL);

    int count = 0;
    char text[1000] = "";
    sprintf(text, "%s", "Enter coefficients: a b c\n");
    outputLog(text);
    printf(text);
    if ((count = scanf("%lg %lg %lg", a, b, c)) < 3)
    {
        inputLog(count);
        sprintf(text, "Error: the format does not match the sample. Variables read: %d\n", count);
        printf(text);
        textToLog(ERROR, text);
    }
    inputLog(3);
    sprintf(text, "a = %d, b = %d, c = %d\n", *a, *b, *c);
    textToLog(EMPTY, text);
}

NumberOfRoots_t solveSquare(double a, double b, double c, double *x1, double *x2)
{
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

    if (areEqualDoubleNumbers(D, 0))
    {
        *x1 = -b / (2 * a);
        if (areEqualDoubleNumbers(*x1, 0))
            *x1 = 0;
        return ONE_ROOT;
    }

    *x1 = (-b - sqrt(D)) / (2 * a);
    if (areEqualDoubleNumbers(*x1, 0))
        *x1 = 0;
    *x2 = (-b + sqrt(D)) / (2 * a);
    if (areEqualDoubleNumbers(*x2, 0))
        *x2 = 0;
    return TWO_ROOTS;
}


NumberOfRoots_t solveLinear(double a, double b, double *ans)
{
    assert(std::isfinite(a) && std::isfinite(b));
    assert(ans != NULL);

    if (a == 0)
    {
        return (b == 0) ? INF_ROOTS : NO_ROOTS;
    }

    *ans = -b / a;
    if (areEqualDoubleNumbers(*ans, 0))
        *ans = 0;
    return ONE_ROOT;
}

double discriminant(double a, double b, double c)
{
    assert(std::isfinite(a) && std::isfinite(b) && std::isfinite(c));
    return (b * b - 4 * a * c);
}

void printAnswer(NumberOfRoots_t nRoots, double root1, double root2)
{
    char text[1000] = "";
    switch (nRoots)
    {
        case NO_ROOTS:
            sprintf(text, "No solutions\n");
            break;
        case ONE_ROOT:
            sprintf(text, "x = %lg\n", root1);
            break;
        case TWO_ROOTS:
            sprintf(text, "x1 = %lg, x2 = %lg\n", root1, root2);
            break;
        case INF_ROOTS:
            sprintf(text, "Any value\n");
            break;
        default:
            sprintf(text, "Unreachable\n");
    }
    printf(text);
    textToLog(INFO, text);
}

void sPrintAnswer(char *target, NumberOfRoots_t nRoots, double root1, double root2)
{
    assert(target != NULL);
    assert(isfinite(root1) && isfinite(root2));
    assert(nRoots == nRoots);

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

bool areEqualDoubleNumbers(double a, double b)
{
    assert(isfinite(a) && isfinite(b));

    if (abs(a-b) < epsilon)
    {
        return true;
    }
    return false;
}