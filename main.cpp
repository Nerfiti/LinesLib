#include "linesLib.h"
#include "stdio.h"
int main()
{
    const int MAXIMUM_LINES_IN_THE_FILE = 100;
    char **lines;
    int nChar_in_lines[MAXIMUM_LINES_IN_THE_FILE];
    FILE *file = fopen("./Strings.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the file.");
        return 0;
    }
    int nLines_f = f_get_nLines(file, nChar_in_lines, MAXIMUM_LINES_IN_THE_FILE);
    printf("%d\n", nLines_f);

    lines = f_read_lines(file, nLines_f, nChar_in_lines);
    lines_sort(lines, nLines_f, nChar_in_lines);
    fclose(file);
    file = fopen("Output.txt", "w");
    f_print_lines(file, lines, nLines_f);
}
