#include "ProgramHelper.h"
#include "stdio.h"

ProgramMode_t getProgramMode(int argc, const char **argv)
{
    if (argc >= 2)
    {
        switch (argv[1][1])
        {
            case 'h':
            {
                textToLog(INFO, "The user requested help information\n");
                return BREAK;
            }
            case 't':
            {
                textToLog(INFO, "The user chose the program mode: UNIT_TEST\n");
                return UNIT_TEST;
            }
            case 'r':
            {
                textToLog(INFO, "The user chose the program mode: RANDOM_TEST\n");
                return RANDOM_TEST;
            }
            case 'f':
            {
                textToLog(INFO, "The user chose the program mode: UNIT_TEST_OF_THE_FILE\n");
                return UNIT_TEST_OF_THE_FILE;
            }
            case 's':
            {
                textToLog(INFO, "The user chose the program mode: SOLVE\n");
                return SOLVE;
            }
            default:
            {
                textToLog(ERROR, "The user chose non-existent program mode.\n");
                printf("Error: the flag does not exist\n");
                return BREAK;
            }
        }
    }
    else
    {
        printf("Error: Not enough arguments");
        textToLog(ERROR, "The user did not enter enough arguments.\n");
        return BREAK;
    }
}

void helperMode()
{
    printf(        "\n-----------------------------------------------------------------------------------------------------------\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "\n"
                   "                                             Equation Project\n"
                   "\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "\n"
                   "The program can solve square equations\n"
                   "\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "\n"
                   "When running from the command line:\n"
                   "\n"
                   "flag -t start the program with mode UNIT_TEST (Automatically standart tests)\n"
                   "flag -r start the program with mode RANDOM_TEST (You can get input and output and can compare it)\n"
                   "flag -f start the program with mode UNIT_TEST_OF_THE_FILE (Tests from file)\n"
                   "flag -s start the program with mode SOLVE (Manual input of coefficients)\n"
                   "\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "\n"
                   "The test file should contain 6 numbers in each line separated by a space. The number of lines is unlimited.\n"
                   "\n"
                   "First number - first coefficient\n"
                   "Second number - second coefficient\n"
                   "Third number - third coefficient\n"
                   "Fourth number - first right answer\n"
                   "Fifth number - second right answer\n"
                   "Sixth number - number of roots (-1, if the number of answers is infinite) \n"
                   "\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "-----------------------------------------------------------------------------------------------------------\n\n");
}