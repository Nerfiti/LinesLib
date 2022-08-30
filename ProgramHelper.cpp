#include "ProgramHelper.h"
#include "stdio.h"

ProgramMode getProgramMode(const int argc, const char **argv)
{
    if (argc >= 2)
    {
        switch (argv[1][1])
        {
            case 'h':
            {
                return HELP;
            }
            case 't':
            {
                return UNIT_TEST;
            }
            case 'f':
            {
                if (argc < 3)
                {
                    printf("Error: not enough arguments.\n");
                    return HELP;
                }
                return UNIT_TEST_OF_THE_FILE;
            }
            case 's':
            {
                if (argc < 3)
                {
                    printf("Error: not enough arguments.\n");
                    return HELP;
                }
                return FILE_SORT;
            }
            default:
            {
                printf("Error: the flag does not exist\n");
                return HELP;
            }
        }
    }
    else
    {
        printf("Error: Not enough arguments.\n");
        return HELP;
    }
}

void helperMode()
{
    printf(      "\n-----------------------------------------------------------------------------------------------------------\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "\n"
                   "                                             LinesLib Project\n"
                   "\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "\n"
                   "This program has functions for reading lines from a file, operations on lines, printing them and a simple \n"
                   "implementation of sorting strings from a file\n"
                   "\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "\n"
                   "Command line flags:\n"
                   "\n"
                   "flag -t start the program with mode UNIT_TEST (Automatically standart tests).\n"
                   "\n"
                   "flag -s start the program with mode SORT_FILE (The lines in the file will be sorted and placed in the \n"
                   "file \"output.txt\") after this flag, you must enter the file name.\n"
                   "\n"
                   "flag -f start the program with mode UNIT_TEST_OF_THE_FILE (Tests from file) after this flag \n"
                   "you must enter the file name.\n"
                   "\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "\n"
                   "The test file should contain 9 objects in each line, separated by a space\n"
                   "\n"
                   "First object - first line.\n"
                   "\n"
                   "Second object - second line.\n"
                   "\n"
                   "Third object - target symbol.\n"
                   "\n"
                   "Fourth object - the position number of the target symbol in the first line.\n"
                   "\n"
                   "Fifth object - the position number of the target symbol in the second line.\n"
                   "\n"
                   "Sixth object - line resulting from concatenation first line and second line\n"
                   "\n"
                   "Seventh object - length of the first line\n"
                   "\n"
                   "Eighth object - length of the second line\n"
                   "\n"
                   "Nints object - positive number (if line1 > line2), 0 (if line1 == line2) or \n"
                   "negative number (if line1 < line2)\n"
                   "\n"
                   "-----------------------------------------------------------------------------------------------------------\n"
                   "-----------------------------------------------------------------------------------------------------------\n\n");
}