#include "Eqlogger.h"
#include "stdio.h"
#include "time.h"
#include "string.h"

FILE *fp = fopen("logs.txt", "w");

void startProgramLog()
{
    fprintf(fp, "[Info] Program started.\n");
}

void endProgramLog()
{
    fprintf(fp, "[Info] Program ended.\n");
    fclose(fp);
}

void inputLog(int numberOfVariables)
{
    fprintf(fp, "[Info] User entered the data. Set %d variable(-s): ", numberOfVariables);
}

void outputLog(char *output)
{
    fprintf(fp, "[Info] Program output: %s\n", output);
}

void openFileLog(char *filename)
{
    fprintf(fp, "[Info] File opened: %s\n", filename);
}

void closeFileLog(char *filename)
{
    fprintf(fp, "[Info] File closed: %s\n", filename);
}

void textToLog(TypeLogMessage_t type, char *text)
{
    if (type == EMPTY)
        fprintf(fp, "%s", text);
    if (type == INFO)
        fprintf(fp, "%s %s", "[Info]", text);
    if (type == ERROR)
        fprintf(fp, "%s %s", "[Error]", text);
    if (type == COMPLETE)
        fprintf(fp, "%s %s", "[Complete]", text);
    if (type == FAIL)
        fprintf(fp, "%s %s", "[Fail]", text);
}