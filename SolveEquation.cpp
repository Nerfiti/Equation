#include "math.h"
#include "assert.h"
#include "stdio.h"
#include "SolveEquation.h"

/// The smallest possible positive value of a double variable
const double epsilon = 10e-8;

void inputCoefficients(FILE *logfile, double *a, double *b, double *c)
{
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    int count = 0;
    char text[1000] = "Enter coefficients: a b c\n";
    outputLog(logfile, text);
    if ((count = scanf("%lg %lg %lg", a, b, c)) < 3)
    {
        inputLog(logfile, count);
        sprintf(text, "Error: the format does not match the sample. Variables read: %d\n", count);
        printf("%s", text);
        textToLog(logfile, ERROR, text);
    }
    inputLog(logfile, 3);
    sprintf(text, "a = %lg, b = %lg, c = %lg\n", *a, *b, *c);
    textToLog(logfile, EMPTY, text);
}

NumberOfRoots solveSquare(double a, double b, double c, double *x1, double *x2)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x2 != NULL);
    assert(x1 != NULL);
    assert(x1 != x2);

    if (a == 0)
    {
        return solveLinear(b, c, x1);
    }

    double disc = discriminant(a, b, c);
    if (compareDoubleNumbers(disc, 0) < 0)
    {
        return NO_ROOTS;
    }

    if (compareDoubleNumbers(disc, 0) == 0)
    {
        *x1 = -b / (2 * a);
        if (compareDoubleNumbers(*x1, 0) == 0)
        {
            *x1 = 0;
        }
        return ONE_ROOT;
    }

    *x1 = (-b - sqrt(disc)) / (2 * a);
    if (compareDoubleNumbers(*x1, 0) == 0)
    {
        *x1 = 0;
    }
    *x2 = (-b + sqrt(disc)) / (2 * a);
    if (compareDoubleNumbers(*x2, 0) == 0)
    {
        *x2 = 0;
    }
    return TWO_ROOTS;
}


NumberOfRoots solveLinear(double a, double b, double *ans)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(ans != NULL);

    if (a == 0)
    {
        return (b == 0) ? INF_ROOTS : NO_ROOTS;
    }

    *ans = -b / a;
    if (compareDoubleNumbers(*ans, 0) == 0)
    {
        *ans = 0;
    }
    return ONE_ROOT;
}

double discriminant(double a, double b, double c)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    return (b * b - 4 * a * c);
}

void printAnswer(FILE *logfile, NumberOfRoots nRoots, double root1, double root2)
{
    char text[1000] = "";
    sPrintAnswer(text, nRoots, root1, root2);
    printf(text);
    textToLog(logfile, INFO, text);
}

void sPrintAnswer(char *target, NumberOfRoots nRoots, double root1, double root2)
{
    assert(target != NULL);
    assert(isfinite(root1));
    assert(isfinite(root2));
    assert(nRoots == nRoots);

    switch (nRoots)
    {
        case NO_ROOTS:
        {
            sprintf(target, "No solutions");
            break;
        }
        case ONE_ROOT:
        {
            sprintf(target, "x = %lg", root1);
            break;
        }
        case TWO_ROOTS:
        {
            sprintf(target, "x1 = %lg, x2 = %lg", root1, root2);
            break;
        }
        case INF_ROOTS:
        {
            sprintf(target, "Any value");
            break;
        }
        default:
        {
            sprintf(target, "Unreachable");
        }
    }
}

int compareDoubleNumbers(double a, double b)
{
    assert(isfinite(a));
    assert(isfinite(b));

    if (abs(a-b) < epsilon)
    {
        return 0;
    }
    if (a - b <= -epsilon)
    {
        return -1;
    }
    return 1;
}