#ifndef UNITTESTEQUATION_H
#define UNITTESTEQUATION_H

#include "enumberOfRoots.h"
#include "stdio.h"
#include "Eqlogger.h"

struct Test_case {
    double a = 0;
    double b = 0;
    double c = 0;
    double ans1 = 0;
    double ans2 = 0;
    NumberOfRoots_t nRoots = NO_ROOTS;
};

enum FailReasons_t {
    WrongNumberOfRoots,
    WrongAnswer,
    WrongAnswers
};

//----------------------------------------------------------------------
//! Test of the SolveEquation's work with standart test cases
//!
//! \return have the test been completed (true or false)
//----------------------------------------------------------------------
bool stdTestEquation();

//----------------------------------------------------------------------
//! Test of the SolveEquation's work
//!
//! \param num number of the test
//! \param a First coefficient
//! \param b Second coefficient
//! \param c Third coefficient
//! \param eans1 First expected answer
//! \param eans2 Second expected answer (if number of roots == TWO_ROOTS)
//! \param enRoots expected number of roots
//!
//! \return have the test been completed (true or false)
//----------------------------------------------------------------------
bool TestEquation(int num, double a, double b, double c, double expectedAns1, double expectedAns2, NumberOfRoots_t expectedNRoots);

//----------------------------------------------------------------------
//! Test of the SolveEquation's work
//!
//!\param [in] num number of the test
//!\param [in] testCase test case
//!
//! \return have the test been completed (true or false)
//----------------------------------------------------------------------
bool TestEquation(int num, Test_case testCase);

//----------------------------------------------------------------------
//! Test of the SolveEquation's work
//!
//!\param [in] testCase test case
//!\param [in] count number of test cases
//!
//! \return have all the tests been completed (true or false)
//----------------------------------------------------------------------
bool TestEquation(Test_case testCase[], int count);

//----------------------------------------------------------------------
//! Test of the SolveEquation's work
//!
//!\param filename name of file
//!
//! \return have all the tests been completed (true or false)
//----------------------------------------------------------------------
bool TestEquation(char *filename);

//----------------------------------------------------------------------
//! Get 3 random coefficients and result of SolveEquation's work
//!
//! \param [in] num number of tests
//----------------------------------------------------------------------
void RandomTestEquation(int num);

//----------------------------------------------------------------------
//! Write about complete test
//!
//! \param [in] x number of test
//! \param [in] lastTime time since start the test
//!
//! \return true
//----------------------------------------------------------------------
bool complete(int x);

//----------------------------------------------------------------------
//! Skip line
//!
//! \param fp Pointer to the file
//!
//! \return have all the tests been completed (true or false)
//----------------------------------------------------------------------
void skipLine(FILE *file);

//----------------------------------------------------------------------
//! Write about fail test and reason of fail
//!
//! \param [in] x number of the test
//! \param [in] reason reason of the fail
//! \param [in] nRoots number of roots
//! \param [in] ans1 first answer
//! \param [in] ans2 second answer
//! \param [in] expectedNRoots expected number of roots
//! \param [in] expectedans1 expected first answer
//! \param [in] expectedans2 expexted second answer
//! \param [out] allTests pointer to the flag
//! \param [in] lastTime time since start the test
//!
//! \return false
//-----------------------------------------------------------------------
bool fail(int x, FailReasons_t reason, NumberOfRoots_t nRoots,         double ans1,         double ans2,
                                     NumberOfRoots_t expectedNRoots, double expectedAns1, double expectedAns2);

#endif // UNITTESTEQUATION_H