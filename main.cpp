#include "SolveEquation.h"
#include "UnitTestEquation.h"
#include "enumberOfRoots.h"
#include "stdio.h"
#include "string.h"

enum ProgramMode {
    UNIT_TEST = 0,
    UNIT_TEST_OF_THE_FILE = 1,
    RANDOM_TEST = 2,
    SOLVE = 3
};

int main(int argc, char *argv[]) {
    const int MAXIMUM_LENGTH_OF_THE_FILENAME = 1000;
    
    ProgramMode mode = SOLVE;
    if (argc >= 2 && argv[1][0] == '-' && argv[1][2] == '\0' &&
                                (argv[1][1] == 't' || argv[1][1] == 'r' || argv[1][1] == 'f' || argv[1][1] == 's'))
        {
        int c = argv[1][1];
        if (c == 't')
            mode = UNIT_TEST;
        if (c == 'r')
            mode = RANDOM_TEST;
        if (c == 'f')
            mode = UNIT_TEST_OF_THE_FILE;
        if (c == 's')
            mode = SOLVE;
        }
    else
    {

        int imode = 0;

        printf("0 - UNIT_TEST\n1 - UNIT_TEST_OF_THE_FILE\n2 - RANDOM_TEST\n3 - SOLVE\nChoose program mode:\n");
        if (scanf("%d", &imode) < 1)
            imode = -1;
        switch (imode)
        {
            case 0:
                mode = UNIT_TEST;
                break;
            case 1:
                mode = UNIT_TEST_OF_THE_FILE;
                break;
            case 2:
                mode = RANDOM_TEST;
                break;
            case 3:
                mode = SOLVE;
                break;
            default:
                printf("Non-existent mode\n");
                return 0;
        }
    }

    double a = 0,
           b = 0,
           c = 0,
           x1 = 0,
           x2 = 0;
    switch (mode)
    {
        case SOLVE:
        {
            inputCoefficients(&a, &b, &c);
            NumberOfRoots_t nRoots = solveSquare(a, b, c, &x1, &x2);
            printAnswer(nRoots, x1, x2);
            break;
        }
        case UNIT_TEST:
        {
            (StandartTestEquation()) ? printf("All tests had been passed\n") : printf("Not all tests had been passed\n");
            break;
        }
        case RANDOM_TEST:
        {
            const int numberOfTests = 10;
            RandomTestEquation(numberOfTests);
            break;
        }
        case UNIT_TEST_OF_THE_FILE:
        {
            printf("Enter the path to the file with tests:\n");
            char filename[MAXIMUM_LENGTH_OF_THE_FILENAME] = "";
            scanf("%s", filename);
            (TestEquation(filename)) ? printf("All tests had been passed\n") : printf("Not all tests had been passed\n");
            break;
        }
    }
    return 0;
}




