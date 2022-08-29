#include "assert.h"
#include "linesLib.h"
#include "malloc.h"
#include "ProgramHelper.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "UnitTests.h"

int main(const int argc, const char *argv[])
{
    /*if (argc < 2)
    {
        printf("Error: not enough arguments.\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error opening the file.");
        return 0;
    }

    int nLines = 0;

    timeval start = {},
            finish = {};
    printf("Sorting...\n");
    gettimeofday(&start, NULL);
    char *file_text = file_to_memory(file, &nLines);
    char **lines_array = line_to_lines(file_text, nLines);
    lines_qsort(lines_array, 0, nLines - 1);
    //qsort(lines_array, nLines, sizeof(char *), lines_compare_for_qsort);
    gettimeofday(&finish, NULL);
    fclose(file);

    FILE *out_file = fopen("Output.txt", "w");
    f_print_lines(file, lines_array, nLines);
    fclose(out_file);
    free(file_text);
    free(lines_array);
    printf("File is sorted. Time: %ld ms.\n",
     (finish.tv_sec*1000 + finish.tv_usec/1000) - (start.tv_sec*1000 + start.tv_usec/1000));
    return 0;*/

    ProgramMode mode = getProgramMode(argc, argv);
    switch (mode)
    {
        case FILE_SORT:
        {
            assert(argc > 2);
            int nLines = 0;
            char **lines_array = SortFile(argv[2], &nLines);
            FILE *out_file = fopen("./Output.txt", "w");
            assert(out_file != NULL);
            f_print_lines(out_file, lines_array, nLines);
            free(lines_array);
            fclose(out_file);
            break;
        }
        case UNIT_TEST:
        {
            stdLinesLibTest();
            break;
        }
        case UNIT_TEST_OF_THE_FILE:
        {
            assert(argc > 2);
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
