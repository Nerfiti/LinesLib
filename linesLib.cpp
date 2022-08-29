#include "linesLib.h"
#include "assert.h"
#include <sys/stat.h>
#include "sys/time.h"
#include "ctype.h"
#include "string.h"

const unsigned long int MAXIMUM_LENGTH_OF_THE_LINE = 4294967295;

char **SortFile(const char *filename, int *nLines)
{
    FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("Error opening the file.");
            return NULL;
        }

        timeval start = {},
                finish = {};
        printf("Sorting...\n");
        gettimeofday(&start, NULL);
        char *file_text = file_to_memory(file, nLines);
        char **lines_array = line_to_lines(file_text, *nLines);
        assert(lines_array != NULL);
        lines_qsort(lines_array, 0, *nLines - 1);
        gettimeofday(&finish, NULL);
        fclose(file);
        free(file_text);
        printf("File is sorted. Time: %ld ms.\n",
               (finish.tv_sec*1000 + finish.tv_usec/1000) - (start.tv_sec*1000 + start.tv_usec/1000));
        return lines_array;
}

unsigned long int line_legth(const char *string)
{
    assert(string != NULL);

    int len = 0;
    while (string[len] != '\0' && len < MAXIMUM_LENGTH_OF_THE_LINE)
    {
        len++;
    }
    return len;
}

char *char_in_line(const char *string, char target)
{
    for (const char *search = string; *search != '\0' && search - string < MAXIMUM_LENGTH_OF_THE_LINE; search++)
    {
        if (*search == target)
        {
            return (char *)search;
        }
    }
    return NULL;
}

void lines_copy(char *target, const char *line)
{
    assert(target != NULL && line != NULL);

    while ((*target++ = *line++) != '\0') {}
}

void lines_cat(char *target, const char *add)
{
    assert(target != NULL && add != NULL);

    while (*target != '\0')
    {
        target++;
    }
    lines_copy(target, add);
}

int lines_compare(const char *string1, const char *string2)
{
    assert(string1 != NULL && string2 != NULL);

    int len = 1;
    while (!isalpha(*string1))
    {
        string1++;
    }
    while (!isalpha(*string2))
    {
        string2++;
    }
    while (*string1 == *string2 && *string1 != '\0' && *string2 != '\0' && len < MAXIMUM_LENGTH_OF_THE_LINE)
    {
        string1++;
        string2++;
        len++;
    }
    return (*string1 - *string2);
}

int lines_compare_for_qsort(const void *string1, const void *string2)
{
    const char *line1 = *(const char **)string1;
    const char *line2 = *(const char **)string2;
    return lines_compare(line1, line2);
}

int get_file_size(FILE *file)
{
    struct stat file_stat = {};
    fstat(fileno(file), &file_stat);
    return file_stat.st_size;
}

char *file_to_memory(FILE *file, int *nLines)
{
    assert(file != NULL);

    bool was_alpha = false;
    char *destination = (char *)calloc(get_file_size(file), sizeof(char)),
         *start_text = destination,
         *start_line = destination;
    while ((*destination = getc(file)) != EOF)
    {
        if (isalpha(*destination))
        {
            was_alpha = true;
        }
        if (*destination == '\n')
        {
            if (was_alpha)
            {
                (*nLines)++;
                was_alpha = false;
                start_line = destination + 1;
            }
            else
            {
                destination = start_line - 1;
            }
        }
            destination++;
    }
    (*nLines)++;
    *destination = '\0';
    return start_text;
}

char **line_to_lines(char *text, int nLines)
{
    char **lines = (char **)calloc(nLines, sizeof(char *));
    char **array = lines;
    *lines++ = text++;
    int line_index = 1;
    while (*text != '\0' && line_index <= nLines)
    {
        if (*text == '\n')
        {
            *text = '\0';
            *lines++ = text + 1;
            line_index++;
        }
        text++;
    }

    return array;
}

void lines_qsort(char *lines[], int left, int right)
{
    assert(lines != NULL);

    if (left >= right)
    {
        return;
    }

    int last = left + 1;
    for (int i = left + 1; i <= right; i++)
    {
        if (lines_compare(lines[left], lines[i]) > 0)
        {
            swap(lines, i, last);
            last++;
        }
    }
    swap(lines, left, last - 1);
    lines_qsort(lines, left, last - 1);
    lines_qsort(lines, last, right);
}

void swap(char *lines[], int fIndex, int sIndex)
{
    assert(lines != NULL);
    assert(lines[fIndex] != NULL);
    assert(lines[sIndex] != NULL);
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