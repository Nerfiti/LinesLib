#ifndef UNITTESTS_H
#define UNITTESTS_H
#include "stdio.h"

//Lines lengths in test file must not be more than 100

struct Test_case {
    char *line1 = NULL;
    char *line2 = NULL;
    char target = 0;
    int targetPos1 = 0;
    int targetPos2 = 0;
    char *catlines = NULL;
    int len1 = 0;
    int len2 = 0;
    int comarationIndex = 0;
};


//----------------------------------------------------------------------
//! Test of the LinesLib's work with standard test cases
//!
//! \return have the test been completed (true or false)
//----------------------------------------------------------------------
bool stdLinesLibTest();

//----------------------------------------------------------------------
//! Test of the LinesLib's work
//!
//! \param line1 First line
//! \param line2 Second Line
//! \param target target symbol
//! \param targetPos1 The position number of the target symbol in the line1
//! (NULL if the line1 does not contain a symbol)
//! \param targetPos2 The position number of the target symbol in the line2
//! (NULL if the line2 does not contain a symbol)
//! \param catlines The line resulting from the application of the function lines_cat(line1, line2)
//! \param len1 The length of the first line
//! \param len2 The length of the second line
//! \param comparationIndex positive (if line1 > line2), 0 (if line1 == line2), negative (if line1 < line2)
//!
//! \return have the test been completed (true or false)
//----------------------------------------------------------------------
bool LinesLibTest(int num, char *line1, char *line2, char target, int targetPos1, int targetPos2,
                  char *catlines, unsigned long int len1, unsigned long int len2, int comparationIndex);

//----------------------------------------------------------------------
//! Test of the LinesLib's work
//!
//! \param [in] num test number
//! \param [in] testCase test case
//!
//! \return have the test been completed (true or false)
//----------------------------------------------------------------------
bool LinesLibTest(int num, Test_case testCase);

//----------------------------------------------------------------------
//! Test of the LinesLib's work
//!
//! \param [in] testCase test case
//! \param [in] count number of test cases
//!
//! \return have all the tests been completed (true or false)
//----------------------------------------------------------------------
bool LinesLibTest(Test_case testCase[], int count);

//----------------------------------------------------------------------
//! Test of the LinesLib's work
//!
//! \param filename name of file
//!
//! \return have all the tests been completed (true or false)
//----------------------------------------------------------------------
bool LinesLibTest(const char *filename);

bool Test_char_in_line(char *line, char target, int targetPos);

void skipLine(FILE *file);

#endif // UNITTESTS_H