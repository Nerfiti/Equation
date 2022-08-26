#ifndef EQLOGGER_H
#define EQLOGGER_H

#include "stdio.h"

enum TypeLogMessage_t {
    EMPTY,
    INFO,
    ERROR,
    COMPLETE,
    FAIL
};

//---------------------------------------------------------
//! Get start program log
//---------------------------------------------------------
void startProgramLog();

//---------------------------------------------------------
//! Get end program log
//---------------------------------------------------------
void endProgramLog();

//---------------------------------------------------------
//! Get input log
//!
//! \param [in] numberOfVariables number of variables
//---------------------------------------------------------
void inputLog(int numberOfVariables);

//---------------------------------------------------------
//! Get output log
//!
//! \param [in] output output text
//---------------------------------------------------------
void outputLog(char *output);

//---------------------------------------------------------
//! Get test complete log
//!
//! \param [in] num test number
//---------------------------------------------------------

//---------------------------------------------------------
//! Get open file log
//!
//! \param filename name of opened file
//---------------------------------------------------------
void openFileLog(char *filename);

//---------------------------------------------------------
//! Get close file log
//!
//! \param filename name of opened file
//---------------------------------------------------------
void closeFileLog(char *filename);

//---------------------------------------------------------
//! Get log with given text
void textToLog(TypeLogMessage_t type, char *text);

#endif // EQLOGGER_H