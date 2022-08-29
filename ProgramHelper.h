#ifndef PROGRAMHELPER_H
#define PROGRAMHELPER_H

enum ProgramMode {
    HELP = -1,
    UNIT_TEST = 0,
    UNIT_TEST_OF_THE_FILE = 1,
    FILE_SORT = 2
};

//--------------------------------------------------------------------
//! Get program mode
//!
//! \param argc number of cmd argument
//! \param argv massive of the char* cmd arguments
//!
//! \return program mode
//-------------------------------------------------------------------
ProgramMode getProgramMode(const int argc, const char **argv);

//--------------------------------------------------------------------
//! Get helper info
//--------------------------------------------------------------------
void helperMode();

#endif // PROGRAMHELPER_H
