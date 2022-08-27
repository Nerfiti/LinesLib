#include "linesLib.h"
#include "assert.h"
#include <sys\stat.h>

const int MAXIMUM_LENGTH_OF_THE_LINE = 10000;

bool is_alpha(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int line_legth(const char *string, int maximum_length)
{
    assert(string != NULL);

    int len = 0;
    while(string[len] != '\0' && len++ < maximum_length)
        ;
    return len;
}

int lines_compare(const char *string1, const char *string2, int nCharacters)
{
    assert(string1 != NULL && string2 != NULL);

    int len = 1;
    while (!is_alpha(*string1))
        string1++;
    while (!is_alpha(*string2))
        string2++;
    while(*string1 == *string2 && *string1 != '\0' &&
          *string2 != '\0' && len < nCharacters)
    {
        string1++;
        string2++;
        len++;
    }

    return (*string1 - *string2);
}

char *char_in_line(char *string, int target, int maximum_length) //How to make a "local" const???
{
    for (char *search = string; *search != '\0' && search - string < maximum_length + 1; search++)
    {
        if (*search == target)
            return search;
    }
    return NULL;
}

char *lines_cat(char *target, const char *add, int maximum_length)
{
    assert(target != NULL && add != NULL);

    char *writer = target;
    while (*writer != '\0' && writer - target < maximum_length)
        writer++;
    while ((*writer++ = *add++) != '\0' && writer - target < maximum_length)
        ;
    *writer = '\0';
    return target;
}

char **f_read_lines(FILE *file, int *nLines)
{
    assert(file != NULL);

    int writer = 0;
    struct stat file_stat = {};
    fstat(fileno(file), &file_stat);
    char *destination = (char *)calloc(file_stat.st_size + 1, sizeof(char));

    while((destination[writer] = getc(file)) != EOF)
    {
        if (destination[writer] == '\n')
        {
            (*nLines)++;
        }
        writer++;
    }
    (*nLines)++;
    destination[writer] = '\0';

    char **lines = (char **)calloc(*nLines, sizeof(char *));
    lines[0] = destination;
    writer = 0;
    int line_index = 1;
    while(destination[writer] != '\0' && line_index <= *nLines)
    {
        if(destination[writer] == '\n')
        {
            destination[writer] = '\0';
            lines[line_index] = &destination[writer + 1];
            line_index++;
        }
        writer++;
    }

    return lines;
}

//use c library funcion qsort

void lines_sort(char *lines[], int nLines)
{
    assert(lines != NULL);
    if (nLines == 0)
        return;
    for (int i = 0; i < nLines - 1; i++)
    {
        if (lines_compare(lines[i], lines[i+1], MAXIMUM_LENGTH_OF_THE_LINE) > 0)
        {
            swap(lines, i, i+1);
        }

    }
    lines_sort(lines, nLines - 1);
}

void swap(char *lines[], int fIndex, int sIndex)
{
    char *temp = lines[fIndex];
    lines[fIndex] = lines[sIndex];
    lines[sIndex] = temp;
}

void f_print_lines(FILE *file, char *lines[], int nLines)
{
    assert(file != NULL);
    assert(lines != NULL);

    for (int i = 0; i < nLines; i++)
    {
        assert(lines[i] != NULL);

        fprintf(file, "%s\n", lines[i]);
    }
}