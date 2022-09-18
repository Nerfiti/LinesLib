#include "assert.h"
#include "linesLib.h"
#include "ProgramHelper.h"
#include "UnitTests.h"

int main(const int argc, const char *argv[])
{
    ProgramMode mode = getProgramMode(argc, argv);
    switch (mode)
    {
        case FILE_SORT:
        {
            assert(argc == 3);
            SortFile(argv[2], false, true);
            break;
        }
        case UNIT_TEST:
        {
            stdLinesLibTest();
            break;
        }
        case UNIT_TEST_OF_THE_FILE:
        {
            assert(argc == 3);
            LinesLibTest(argv[2]);
            break;
        }
        case HELP:
        {
            helperMode();
            break;
        }
    }
    return 0;

}
