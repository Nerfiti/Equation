#ifndef PROGRAMHELPER_H
#define PROGRAMHELPER_H

#include "Eqlogger.h"

enum ProgramMode_t {
    BREAK = -1,
    UNIT_TEST = 0,
    UNIT_TEST_OF_THE_FILE = 1,
    RANDOM_TEST = 2,
    SOLVE = 3
};

//--------------------------------------------------------------------
//! Get program mode
//!
//! \param argc number of cmd argument
//! \param argv massive of the char* arguments
//!
//! \return program mode
//-------------------------------------------------------------------
ProgramMode_t getProgramMode(int argc, const char **argv);

//--------------------------------------------------------------------
//! Get helper info
//--------------------------------------------------------------------
void helperMode();

#endif // PROGRAMHELPER_H
