#include "linesLib.h"
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "sys/time.h"

int main(int argc, char *argv[])
{
    argc = 2;
    char tempname[100] = "C:/Users/penko/Downloads/Eugene Onegin.txt";
    if (argc < 2)
    {
        printf("Error: not enough arguments.\n");
        return 0;
    }

    FILE *file = fopen(tempname, "r");
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
    lines_sort(lines_array, 0, nLines - 1);
    //qsort(lines_array, nLines, sizeof(char *), lines_compare_for_qsort);
    gettimeofday(&finish, NULL);
    fclose(file);

    FILE *out_file = fopen("Output.txt", "w");
    f_print_lines(file, lines_array, nLines);
    fclose(out_file);
    free(file_text);
    free(lines_array);
    printf("File are sorted. Time: %ld ms.", (finish.tv_sec*1000 + finish.tv_usec/1000) - (start.tv_sec*1000 + start.tv_usec/1000));
    return 0;
}
