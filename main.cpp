#include "linesLib.h"
#include "stdio.h"
#include <sys\stat.h>
#include "malloc.h"

const int MAXIMUM_LENGTH_OF_THE_FILENAME = 1000;

int main(int argc, char *argv[])
{
    //argc = 2;
    //argv[1] = "./Strings.txt";
    if (argc < 2)
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
    char **lines_array = f_read_lines(file, &nLines);
    printf("\nSorting...\n");
    lines_sort(lines_array, nLines);
    fclose(file);

    file = fopen("Output.txt", "w");
    f_print_lines(file, lines_array, nLines);
    fclose(file);
    f_print_lines(stdout, lines_array, nLines);
}
