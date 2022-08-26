#include "UnitTestEquation.h"
#include "SolveEquation.h"
#include "random"
#include "assert.h"
#include "Eqlogger.h"

const int MAXIMUM_MESSAGE_LENGTH = 1000;

bool TestEquation(int num, double a, double b, double c, double expectedAns1, double expectedAns2, NumberOfRoots_t expectedNRoots)
{
    assert(std::isfinite(expectedAns1) && std::isfinite(expectedAns2));

    double ans1 = 0,
           ans2 = 0;
    NumberOfRoots_t nRoots = solveSquare(a, b, c, &ans1, &ans2);

    if (nRoots != expectedNRoots)
    {
        return fail(num, WrongNumberOfRoots, nRoots,         ans1,         ans2,
                                                   expectedNRoots, expectedAns1, expectedAns2);
    }
    if (nRoots == INF_ROOTS || nRoots == NO_ROOTS)
    {
        return complete(num);
    }
    if (nRoots == ONE_ROOT)
    {
        return
        (areEqualDoubleNumbers(ans1, expectedAns1)) ?
        complete(num) :
        fail(num, WrongAnswer, nRoots,         ans1,         ans2,
                                                expectedNRoots, expectedAns1, expectedAns2);
    }
    return
    ((areEqualDoubleNumbers(ans1, expectedAns1) && areEqualDoubleNumbers(ans2, expectedAns2)) || ((areEqualDoubleNumbers(ans1, expectedAns2) && areEqualDoubleNumbers(ans2, expectedAns1)))) ?
    complete(num) :
    fail(num, WrongAnswers, nRoots,         ans1,         ans2,
                                             expectedNRoots, expectedAns1, expectedAns2);
}

bool TestEquation(int num, Test_case testCase)
{
    return TestEquation(num, testCase.a, testCase.b, testCase.c, testCase.ans1, testCase.ans2, testCase.nRoots);
}

bool TestEquation(Test_case testCase[], int count)
{
    char text[MAXIMUM_MESSAGE_LENGTH] = "";
    int numberOfAccessTests = 0;
    bool allTests = true;
    for (int i = 0; i < count; i++)
    {
        if(!TestEquation(i+1, testCase[i]))
            allTests = false;
        else
            numberOfAccessTests++;
    }
    sprintf(text, "TestEquation: %d/%d tests had been passed.\n", numberOfAccessTests, count);
    textToLog(INFO, text);
    printf("%s", text);
    return allTests;
}

bool TestEquation(char *filename)
{
    char text[MAXIMUM_MESSAGE_LENGTH] = "";
    double a = 0,
           b = 0,
           c = 0,
           ans1 = 0,
           ans2 = 0;
    NumberOfRoots_t nRoots = NO_ROOTS;
    bool allTests = true;
    int num = 1,
        flag = 0,
        numberOfTests = 0,
        numberOfAccesTests = 0;
    FILE *file = fopen(filename, "r");//!

    if (file == NULL){
        sprintf(text, "Error opening the file: %s.\n", filename);
        textToLog(ERROR, text);
        printf("%s", text);
        return false;
    }
    openFileLog(filename);

    while ((flag = fscanf(file, "%lg %lg %lg %lg %lg %d", &a, &b, &c, &ans1, &ans2, &nRoots)) != EOF)
        {
        numberOfTests++;
            if (flag < 6) {
                sprintf(text, "Error in test %d: the format does not match the sample\n", num);
                textToLog(ERROR, text);
                printf("%s", text);
                allTests = false;
                skipLine(file);
                continue;
            }
            if (!TestEquation(num++, a, b, c, ans1, ans2, nRoots))
            {
                numberOfAccesTests--;
                allTests = false;
            }
            skipLine(file);
            numberOfAccesTests++;
        }
    sprintf(text, "TestEquation: %d/%d tests had been passed.\n", numberOfAccesTests, numberOfTests);
    textToLog(INFO, text);
    printf("%s", text);
    fclose(file);
    closeFileLog(filename);
    return allTests;
}

bool stdTestEquation()
{
    textToLog(INFO, "Start standart testing\n");
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

void skipLine(FILE *file)
{
    int ch = 0;
    while((ch = getc(file)) != EOF && ch != '\n')
        ;
}

void RandomTestEquation(int num)
{
    textToLog(INFO, "Random testing started.\n");
    char answers[MAXIMUM_MESSAGE_LENGTH] = "";
    for (int i = 0; i < num; i++)
    {
        double a = rand(),
               b = rand(),
               c = rand(),
               x1 = 0,
               x2 = 0;
        NumberOfRoots_t nRoots = solveSquare(a, b, c, &x1, &x2);
        sPrintAnswer(answers, nRoots, x1, x2);
        printf("Input: a = %6lg, b = %6lg, c = %6lg. Output: %s\n", a, b, c, answers);
    }
}

bool complete(int x)
{
    char text[MAXIMUM_MESSAGE_LENGTH] = "";
    sprintf(text, "Test %d complete.\n", x);
    textToLog(COMPLETE, text);
    printf("%s", text);
    return true;
}

bool fail(int x, FailReasons_t reason, NumberOfRoots_t nRoots, double ans1, double ans2,
          NumberOfRoots_t expectedNRoots, double expectedAns1, double expectedAns2)
{
    char log[MAXIMUM_MESSAGE_LENGTH];
    if (reason == WrongNumberOfRoots)
    {
        sprintf(log, "Test %d fail: Wrong number of roots. Number of roots = %d. Expected: %d.\n", x, nRoots,
                expectedNRoots);
        printf("%s", log);
    }
    else if (reason == WrongAnswer)
    {
        sprintf(log, "Test %d fail: Wrong answer. x = %lg. Expected: x = %lg.\n", x, ans1,
                expectedAns1);
        printf("%s", log);
    }
    else
    {
        sprintf(log, "Test %d fail: Wrong answers. x1 = %lg, x2 = %lg. Expected: x1 = %lg, x2 = %lg.\n", x, ans1, ans2,
               expectedAns1, expectedAns2);
        printf("%s", log);
    }
    textToLog(FAIL, log);
    return false;
}