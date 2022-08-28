#include "Eqlogger.h"

void startProgramLog(FILE *logfile)
{
    fprintf(logfile, "[Info] Program started.\n");
}

void endProgramLog(FILE *logfile)
{
    fprintf(logfile, "[Info] Program ended.\n");
}

void inputLog(FILE *logfile, int numberOfVariables)
{
    fprintf(logfile, "[Info] User entered the data. Set %d variable(-s): ", numberOfVariables);
}

void outputLog(FILE *logfile, const char *output)
{
    printf(output);
    fprintf(logfile, "[Info] Program output: %s\n", output);
}

void openFileLog(FILE *logfile, const char *filename)
{
    fprintf(logfile, "[Info] File opened: %s\n", filename);
}

void closeFileLog(FILE *logfile, const char *filename)
{
    fprintf(logfile, "[Info] File closed: %s\n", filename);
}

void textToLog(FILE *logfile, TypeLogMessage type, const char *text)
{
    if (type == EMPTY)
        fprintf(logfile, "%s", text);
    if (type == INFO)
        fprintf(logfile, "%s %s", "[Info]", text);
    if (type == ERROR)
        fprintf(logfile, "%s %s", "[Error]", text);
    if (type == COMPLETE)
        fprintf(logfile, "%s %s", "[Complete]", text);
    if (type == FAIL)
        fprintf(logfile, "%s %s", "[Fail]", text);
}