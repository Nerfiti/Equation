#include "SolveEquation.h"
#include "UnitTestEquation.h"
#include "enumberOfRoots.h"
#include "stdio.h"
#include "ProgramHelper.h"
#include "Eqlogger.h"
#include "assert.h"

const int MAXIMUM_LENGTH_OF_THE_FILENAME = 1000;

int main(const int argc, const char **argv)
{
    FILE *logfile = fopen("logs.txt", "w");
    startProgramLog(logfile);
    double  a = 0,
            b = 0,
            c = 0,
           x1 = 0,
           x2 = 0;

    ProgramMode mode = getProgramMode(logfile, argc, argv);
    switch (mode)
    {
        case SOLVE:
        {
            assert(argc > 4);
            textToLog(logfile, INFO, "The program works in the mode SOLVE\n");
            NumberOfRoots nRoots = solveSquare(atof(argv[2]), atof(argv[3]), atof(argv[4]), &x1, &x2);
            printAnswer(logfile, nRoots, x1, x2);
            break;
        }
        case UNIT_TEST:
        {
            textToLog(logfile, INFO, "The program works in the mode UNIT_TEST\n");
            stdTestEquation(logfile);
            break;
        }
        case RANDOM_TEST:
        {
            assert(argc > 2);

            textToLog(logfile, INFO, "The program works in the mode RANDOM_TEST\n");
            const int numberOfTests = atoi(argv[2]);
            RandomTestEquation(logfile, numberOfTests);
            break;
        }
        case UNIT_TEST_OF_THE_FILE:
        {
            assert(argc > 2);

            textToLog(logfile, INFO, "The program works in the mode UNIT_TEST_OF_THE_FILE\n");
            printf("Opening file fith path: \"%s\"...\n", argv[2]);
            TestEquation(logfile, argv[2]);
            break;
        }
        case HELP:
        {
            helperMode();
            break;
        }
    }
    endProgramLog(logfile);
    fclose(logfile);
    return 0;
}
