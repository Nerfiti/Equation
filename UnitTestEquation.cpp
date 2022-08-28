#include "UnitTestEquation.h"
#include "SolveEquation.h"
#include "random"
#include "assert.h"
#include "Eqlogger.h"
#include "math.h"

const int MAXIMUM_MESSAGE_LENGTH = 1000;

bool TestEquation(FILE *logfile, int num, double a, double b, double c,
                  double expectedAns1, double expectedAns2,
                  NumberOfRoots expectedNRoots)
{
    assert(isfinite(expectedAns1));
    assert(isfinite(expectedAns2));

    double ans1 = 0,
           ans2 = 0;
    NumberOfRoots nRoots = solveSquare(a, b, c, &ans1, &ans2);

    if (nRoots != expectedNRoots)
    {
        return fail(logfile, num, WrongNumberOfRoots, nRoots,         ans1,         ans2,
                                             expectedNRoots, expectedAns1, expectedAns2);
    }
    if (nRoots == INF_ROOTS || nRoots == NO_ROOTS)
    {
        return complete(logfile, num);
    }
    if (nRoots == ONE_ROOT)
    {
        return
            (compareDoubleNumbers(ans1, expectedAns1) == 0) ?
            complete(logfile, num) :
            fail(logfile, num, WrongAnswer, nRoots,         ans1,         ans2,
                                   expectedNRoots, expectedAns1, expectedAns2);
    }
    return
        ((compareDoubleNumbers(ans1, expectedAns1) == 0 && compareDoubleNumbers(ans2, expectedAns2) == 0) ||
        ((compareDoubleNumbers(ans1, expectedAns2) == 0 && compareDoubleNumbers(ans2, expectedAns1) == 0))) ?
        complete(logfile, num) :
        fail(logfile, num, WrongAnswers, nRoots,         ans1,         ans2,
                                expectedNRoots, expectedAns1, expectedAns2);
}

bool TestEquation(FILE *logfile, int num, Test_case testCase)
{
    return TestEquation(logfile, num, testCase.a, testCase.b, testCase.c, testCase.ans1, testCase.ans2, testCase.nRoots);
}

bool TestEquation(FILE *logfile, Test_case testCase[], int count)
{
    char text[MAXIMUM_MESSAGE_LENGTH] = "";
    int numberOfAccessTests = 0;
    bool allTests = true;
    for (int i = 0; i < count; i++)
    {
        if(!TestEquation(logfile, i+1, testCase[i]))
        {
            allTests = false;
        }
        else
        {
            numberOfAccessTests++;
        }
    }
    sprintf(text, "TestEquation: %d/%d tests had been passed.\n", numberOfAccessTests, count);
    textToLog(logfile, INFO, text);
    printf("%s", text);
    return allTests;
}

bool TestEquation(FILE *logfile, const char *filename)
{
    NumberOfRoots nRoots = NO_ROOTS;
    bool allTests = true;
    char text[MAXIMUM_MESSAGE_LENGTH] = "";
    double a = 0,
           b = 0,
           c = 0,
           ans1 = 0,
           ans2 = 0;
    int num = 1,
        flag = 0,
        numberOfTests = 0,
        numberOfPassedTests = 0;
    FILE *file = fopen(filename, "r");//!
    if (file == NULL)
    {
        sprintf(text, "Error opening the file: \"%s\".\n", filename);
        textToLog(logfile, ERROR, text);
        printf("%s", text);
        return false;
    }
    openFileLog(logfile, filename);

    while ((flag = fscanf(file, "%lg %lg %lg %lg %lg %d", &a, &b, &c, &ans1, &ans2, &nRoots)) != EOF)
    {
        numberOfTests++;
            if (flag < 6)
            {
                sprintf(text, "Error in test %d: the format does not match the sample\n", num);
                textToLog(logfile, ERROR, text);
                printf("%s", text);
                allTests = false;
                skipLine(file);
                continue;
            }
            if (!TestEquation(logfile, num++, a, b, c, ans1, ans2, nRoots))
            {
                numberOfPassedTests--;
                allTests = false;
            }
            skipLine(file);
            numberOfPassedTests++;
    }

    sprintf(text, "TestEquation: %d/%d tests had been passed.\n", numberOfPassedTests, numberOfTests);
    textToLog(logfile, INFO, text);
    printf("%s", text);
    fclose(file);
    closeFileLog(logfile, filename);
    return allTests;
}

bool stdTestEquation(FILE *logfile)
{
    textToLog(logfile, INFO, "Start standart testing\n");
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
    return TestEquation(logfile, test, numberOfTests);
}

void skipLine(FILE *file)
{
    int ch = 0;
    while((ch = getc(file)) != EOF && ch != '\n') {}
}

void RandomTestEquation(FILE *logfile, int num)
{
    textToLog(logfile, INFO, "Random testing started.\n");
    char answers[MAXIMUM_MESSAGE_LENGTH] = "";
    for (int i = 0; i < num; i++)
    {
        double a = rand(),
               b = rand(),
               c = rand(),
               x1 = 0,
               x2 = 0;
        NumberOfRoots nRoots = solveSquare(a, b, c, &x1, &x2);
        sPrintAnswer(answers, nRoots, x1, x2);
        printf("Input: a = %7lg, b = %7lg, c = %7lg. Output: %s\n", a, b, c, answers);
    }
}

bool complete(FILE *logfile, int x)
{
    char text[MAXIMUM_MESSAGE_LENGTH] = "";
    sprintf(text, "Test %d complete.\n", x);
    textToLog(logfile, COMPLETE, text);
    printf("%s", text);
    return true;
}

bool fail(FILE *logfile, int x, FailReasons reason, NumberOfRoots nRoots, double ans1, double ans2,
                                                    NumberOfRoots expectedNRoots, double expectedAns1, double expectedAns2)
{
    char log[MAXIMUM_MESSAGE_LENGTH];
    if (reason == WrongNumberOfRoots)
    {
        sprintf(log, "Test %d fail: Wrong number of roots. Number of roots = %d. Expected: %d.\n", x, nRoots,
                expectedNRoots);
    }
    else if (reason == WrongAnswer)
    {
        sprintf(log, "Test %d fail: Wrong answer. x = %lg. Expected: x = %lg.\n", x, ans1,
                expectedAns1);
    }
    else
    {
        sprintf(log, "Test %d fail: Wrong answers. x1 = %lg, x2 = %lg. Expected: x1 = %lg, x2 = %lg.\n", x, ans1, ans2,
               expectedAns1, expectedAns2);
    }
    printf("%s", log);
    textToLog(logfile, FAIL, log);
    return false;
}