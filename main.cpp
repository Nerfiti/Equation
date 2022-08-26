#include "SolveEquation.h"
#include "UnitTestEquation.h"
#include "enumberOfRoots.h"
#include "stdio.h"
#include "ProgramHelper.h"
#include "Eqlogger.h"

int main(int argc, const char **argv)
{
    startProgramLog();


    const int MAXIMUM_LENGTH_OF_THE_FILENAME = 1000;
    double a = 0,
           b = 0,
           c = 0,
           x1 = 0,
           x2 = 0;
    ProgramMode_t mode = getProgramMode(argc, argv);
    switch (mode)
    {
        case SOLVE:
        {
            textToLog(INFO, "The program works in the mode SOLVE\n");
            inputCoefficients(&a, &b, &c);
            NumberOfRoots_t nRoots = solveSquare(a, b, c, &x1, &x2);
            printAnswer(nRoots, x1, x2);
            break;
        }
        case UNIT_TEST:
        {
            textToLog(INFO, "The program works in the mode UNIT_TEST\n");
            (stdTestEquation()) ? printf("All tests had been passed\n") : printf("Not all tests had been passed\n");
            break;
        }
        case RANDOM_TEST:
        {
            textToLog(INFO, "The program works in the mode RANDOM_TEST\n");
            const int numberOfTests = 10;
            RandomTestEquation(numberOfTests);
            break;
        }
        case UNIT_TEST_OF_THE_FILE:
        {
            textToLog(INFO, "The program works in the mode UNIT_TEST_OF_THE_FILE\n");
            printf("Enter the path to the file with tests:\n");
            char filename[MAXIMUM_LENGTH_OF_THE_FILENAME] = "";
            scanf("%s", filename);
            TestEquation(filename);// ? printf("All tests had been passed\n") : printf("Not all tests had been passed\n");
            break;
        }
        case BREAK:
        {
            helperMode();
            endProgramLog();
            return 0;
        }
    }
    endProgramLog();
    return 0;
}
