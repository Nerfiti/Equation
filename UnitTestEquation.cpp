#include "UnitTestEquation.h"
#include "enumberOfRoots.h"
#include "SolveEquation.h"
#include "random"
#include "assert.h"

bool StandartTestEquation()
{
    const int numberOfTests = 10;
    Test_case test[numberOfTests] = {
            //a    b    c     ans1          ans2                nRoots
            { 0,   0,   0,     0,            0,               INF_ROOTS},
            { 0,   0,  10,     0,            0,                NO_ROOTS},
            { 0,  -5,  10,     2,            0,                ONE_ROOT},
            { 1,  -2,   1,     1,            0,                ONE_ROOT},
            { 1,  -5,   6,     2,            3,               TWO_ROOTS},
            { 3,   7,   2,    -2,    (double) -1 / 3,         TWO_ROOTS},
            {-2,   0,   4,  sqrt(2),    -sqrt(2),             TWO_ROOTS},
            { 2,  -2,   0,     0,            1,               TWO_ROOTS},
            { 2,  -2,   7,     0,            0,                NO_ROOTS},
            {-1,   2,  -1,     1,            0,                ONE_ROOT}

    };
    return TestEquation(test, numberOfTests);
}

bool TestEquation(int num, double a, double b, double c, double expectedAns1, double expectedAns2, NumberOfRoots_t expectedNRoots)
{
    assert(std::isfinite(expectedAns1) && std::isfinite(expectedAns2));

    bool testComplete = true;
    double ans1 = 0,
           ans2 = 0;
    NumberOfRoots_t nRoots = solveSquare(a, b, c, &ans1, &ans2);

    if (nRoots != expectedNRoots)
    {
        return fail(num, WrongNumberOfRoots, nRoots,         ans1,         ans2,
                                                   expectedNRoots, expectedAns1, expectedAns2);
    }
    if (nRoots == INF_ROOTS || nRoots == NO_ROOTS){
        return complete(num);
    }
    if (nRoots == ONE_ROOT){
        return (ans1 == expectedAns1) ? complete(num) :
            fail(num, WrongAnswer, nRoots,         ans1,         ans2,
                                                expectedNRoots, expectedAns1, expectedAns2);
    }
    return (ans1 == expectedAns1 && ans2 == expectedAns2) ? complete(num) :
        fail(num, WrongAnswers, nRoots,         ans1,         ans2,
                                             expectedNRoots, expectedAns1, expectedAns2);
}

bool TestEquation(int num, Test_case testCase)
{
    return TestEquation(num, testCase.a, testCase.b, testCase.c, testCase.ans1, testCase.ans2, testCase.nRoots);
}

bool TestEquation(Test_case testCase[], int count)
{
    bool allTests = true;
    for (int i = 0; i < count; i++){
        if(!TestEquation(i+1, testCase[i]))
            allTests = false;
    }
    return allTests;
}

bool TestEquation(char *filename){
    double a = 0,
           b = 0,
           c = 0,
           ans1 = 0,
           ans2 = 0;
    NumberOfRoots_t nRoots = NO_ROOTS;
    bool allTests = true;
    int flag = 0,
        ch = 0,
        num = 1;
    FILE *fp = fopen(filename, "r");//!

    if (fp == NULL){
        printf("Error opening the file\n");
        return false;
    }

    while ((flag = fscanf(fp, "%lg %lg %lg %lg %lg %d", &a, &b, &c, &ans1, &ans2, &nRoots)) != EOF){
        if (flag < 6) {
            printf("Error in test %d: the format does not match the sample\n", num);
            allTests = false;
            skipLine(fp);
            continue;
        }
        if (!TestEquation(num++, a, b, c, ans1, ans2, nRoots))
            allTests = false;
        skipLine(fp);
    }
    return allTests;
}

void skipLine(FILE *fp)
{
    int ch = 0;
    while((ch = getc(fp)) != EOF && ch != '\n')
                ;
}

void RandomTestEquation(int num)
{
    char *answers = (char *) malloc(100);//!
    for (int i = 0; i < num; i++)
    {

        double a = rand(),
               b = rand(),
               c = rand(),
               x1 = 0,
               x2 = 0;
        NumberOfRoots_t nRoots = solveSquare(a, b, c, &x1, &x2);
        sPrintAnswer(answers, nRoots, x1, x2);
        printf("Input: a = %lg, b = %lg, c = %lg. Output: %s\n", a, b, c, answers);
    }
}

bool complete(int x)
{
    printf("Test %d complete\n", x);
    return true;
}

bool fail(int x, FailReasons_t reason, NumberOfRoots_t nRoots, double ans1, double ans2,
          NumberOfRoots_t expectedNRoots, double expectedAns1, double expectedAns2)
{
    if (reason == WrongNumberOfRoots)
        printf("Test %d fail: Wrong number of roots. Number of roots = %d. Expected: %d\n", x, nRoots, expectedNRoots);
    else if (reason == WrongAnswer)
        printf("Test %d fail: Wrong answer. x = %lg. Expected: x = %lg\n", x, ans1, expectedAns1);
    else
        printf("Test %d fail: Wrong answers. x1 = %lg, x2 = %lg. Expected: x1 = %lg, x2 = %lg\n", x, ans1, ans2,
               expectedAns1, expectedAns2);
    return false;
}