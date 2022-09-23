#include "assert.h"

#include "linesLib.h"
#include "ProgramHelper.h"
#include "UnitTests.h"

int main(const int argc, const char *argv[])
{
    ProgramMode mode = FILE_SORT;//getProgramMode(argc, argv);
    switch (mode)
    {
        case FILE_SORT:
        {
            //assert(argc >= 3);
            bool reverse = false;
            bool backsort = true;
            SortFile(argv[2], reverse, backsort);
            //SortFile("C:/Users/penko/Downloads/Eugene Onegin.txt", reverse, backsort);
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
        default:
        {
            assert(0 && "The program mode doesn't exist.");
        }
    }
    return 0;

}
