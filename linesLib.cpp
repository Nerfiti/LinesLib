#include "linesLib.h"
#include "assert.h"

// TODO: think about better naming, story about f standing for "first" makes me throw up
int line_legth(const char *string, int maximum_length) // string_length (TODO: think about making this strNlen (note N in name))
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
    while(*string1 == *string2 && *string1 != '\0' && *string2 != '\0' && len < nCharacters)
    {
        string1++;
        string2++;
        len++;
    }

    return (*string1 - *string2);
}

char *char_in_line(char *string, int target, int maximum_length) //Как сделать локальный const???
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

char *f_read_line(FILE *file, int nChar_in_line)
{
    assert(file != NULL);

    char *dst = (char *)calloc(nChar_in_line, sizeof(char));
    char *writer = dst;
    char ch = 0;
    int count = 0;
    while ((ch = getc(file)) != '\n' && ch != EOF && writer - dst < nChar_in_line)
    {
        *writer++ = ch;
        count++;
    }
    *writer = '\0';
    return dst;
}

int f_get_nLines(FILE *file, int *nChar_in_lines, int maximum_Nlines)
{
    assert(file != NULL);
    fseek(file, 0, 0);
    int lines_count = 0,
        char_in_lines_count = 0,
        nChar_in_lines_temp[maximum_Nlines];
    char ch = 0;
    while((ch = getc(file)) != EOF)
    {
        char_in_lines_count++;
        if (ch == '\n')
        {
            nChar_in_lines_temp[lines_count] = ++char_in_lines_count;
            lines_count++;
        }
    }
    for (int i = 0; i < lines_count; i++)
    {
        nChar_in_lines[i] = nChar_in_lines_temp[i];
    }
    fseek(file, 0, 0);
    return (lines_count + 1);
}

char **f_read_lines(FILE *file, int nLines, int *nChar_in_lines)
{
    assert(file != NULL);
    int count = 0;
    char **dstarray = (char **)calloc(nLines, sizeof(char *));
    for (int i = 0; i < nLines; i++)
    {
        dstarray[i] = f_read_line(file, nChar_in_lines[i]);
    }
    return dstarray;
}

void lines_sort(char *lines[], int nLines, int *nChar_in_lines)
{
    assert(lines != NULL);
    if (nLines == 0)
        return;
    for (int i = 0; i < nLines - 1; i++)
    {
        if (lines_compare(lines[i], lines[i+1], nChar_in_lines[i]+2) > 0)
            swap(lines, i, i+1);
    }
    lines_sort(lines, nLines - 1, nChar_in_lines);
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