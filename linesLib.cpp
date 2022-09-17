#include "assert.h"
#include "ctype.h"
#include "linesLib.h"
#include "malloc.h"
#include <sys/stat.h>

const unsigned long int MAXIMUM_LENGTH_OF_THE_LINE = 4294967295;

void SortFile(const char *filename, bool reverse, bool backsort)
{
    int nLines = 0;

    //Open the file with text
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening the file.");
        return;
    }


    printf("Reading the file...\n");
    //Read file and copy it to memory
    char *file_text = (char *)calloc(get_file_size(file), sizeof(char));
    file_to_memory(file, &nLines, file_text);
    if (file_text == NULL)
    {
        printf("File reading error.\n");
        return;
    }
    printf("The file has been read.\n\n");


    printf("Splitting the text of the file into lines...\n");
    //Split the text of the file into lines
    Line *lines_array = (Line *)calloc(nLines, sizeof(Line));
    line_to_lines(file_text, nLines, lines_array);
    if (file_text == NULL)
    {
        printf("Text splitting error.\n");
        return;
    }
    printf("The text has been splitting.\n\n");


    printf("Sorting...\n");
    //Sort text of the file
    lines_qsort(lines_array, 0, nLines - 1, reverse, backsort);
    printf("The file has been sorted.\n\n");


    assert(fclose(file) != EOF);


    //Print sorted text to a file "Output.txt"
    FILE *out_file = fopen("./Output.txt", "w");
    if (out_file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    f_print_lines(out_file, lines_array, nLines);

    free(file_text);
    free(lines_array);

    assert(fclose(out_file) != EOF);
}

int get_file_size(FILE *file)
{
    struct stat file_stat = {};
    fstat(fileno(file), &file_stat);
    return file_stat.st_size;
}

void file_to_memory(FILE *file, int *nLines, char *text)
{
    assert(file != NULL);
    assert(nLines != NULL);

    bool was_alpha = false;
    char *start_line = text;

    while ((*text = getc(file)) != EOF)
    {
        if (isalpha(*text) && *text != 'I' && *text != 'X' && *text != 'V' && *text != 'L')
        {
            was_alpha = true;
        }
        if (*text == '\n')
        {
            if (was_alpha)
            {
                (*nLines)++;
                was_alpha = false;
                start_line = text + 1;
            }
            else
            {
                text = start_line - 1;
            }
        }
        text++;
    }
    (*nLines)++;
    *text = '\0';
}

void line_to_lines(char *text, int nLines, Line *lines)
{
    lines->start = text;
    text++;
    int line_index = 1;
    while (*text != '\0' && line_index <= nLines)
    {
        if (*text == '\n')
        {
            *text = '\0';
            lines->finish = text;
            lines++;
            lines->start = text + 1;
            line_index++;
        }
        text++;
    }
    *text = '\0';
    lines->finish = text;
}

void lines_qsort(Line *lines, int left, int right, bool reverse, bool backsort)
{
    assert(lines != NULL);

    if (left >= right)
    {
        return;
    }

    int last = left + 1;
    for (int i = left + 1; i <= right; i++)
    {
        if (lines_compare(lines[left], lines[i], reverse, backsort) > 0)
        {
            swap(lines, i, last);
            last++;
        }
    }
    swap(lines, left, last - 1);
    lines_qsort(lines, left, last - 1, reverse, backsort);
    lines_qsort(lines, last, right, reverse, backsort);
}

int lines_compare(Line string1, Line string2, bool reverse, bool backsort)
{
    assert(string1.start != NULL && string1.finish != NULL);
    assert(string2.start != NULL && string2.finish != NULL);

    while (!isalpha((backsort) ? *(string1.finish) : *(string1.start)))
    {
        (backsort) ? (string1.finish)-- : (string1.start)++;
    }
    while (!isalpha((backsort) ? *string2.finish : *string2.start))
    {
        (backsort) ? (string2.finish)-- : (string2.start)++;
    }

    if (backsort)
    {
        while (*(string1.finish) == *(string2.finish) &&
                 string1.start  <=   string1.finish &&
                 string2.start  <=   string2.finish)
        {
            (string1.finish)--;
            (string2.finish)--;
        }
    }
    else
    {
        while (*(string1.start) == *(string2.start) &&
                 string1.start  <   string1.finish &&
                 string2.start  <   string2.finish)
        {
            (string1.start)++;
            (string2.start)++;
        }
    }
    return (backsort) ? *(string1.finish) - *(string2.finish) : *(string1.start) - *(string2.start);
}

void swap(Line *lines, int fIndex, int sIndex)
{
    assert(lines != NULL);

    Line temp = lines[fIndex];
    lines[fIndex] = lines[sIndex];
    lines[sIndex] = temp;
}

void f_print_lines(FILE *file, Line *lines, int nLines)
{
    assert(file != NULL);
    assert(lines != NULL);

    for (int i = 0; i < nLines; i++)
    {
        assert(lines[i].start != NULL);

        fprintf(file, "%s\n", lines[i].start);
    }
}

Line string_to_Line(const char *string)
{
    assert(string != NULL);

    Line line = {};
    line.start = (char *)string;
    int len = 0;
    while (string[len] != '\0' && len < MAXIMUM_LENGTH_OF_THE_LINE)
    {
        len++;
    }
    line.finish = (char *)&string[len];
    return line;
}

unsigned long int line_legth(const Line string)
{
    assert(string.start != NULL);
    assert(string.finish != NULL);

    return string.finish - string.start;
}

char *char_in_line(Line string, char target)
{
    assert(string.start != NULL);
    assert(string.finish != NULL);

    for (const char *search = string.start; *search != '\0' &&
                                             search - string.start < MAXIMUM_LENGTH_OF_THE_LINE; search++)
    {
        if (*search == target)
        {
            return (char *)search;
        }
    }
    return NULL;
}

void lines_copy(Line *target, Line prototype)
{
    assert(target != NULL);
    assert(target->start != NULL && target->finish != NULL);
    assert(prototype.start != NULL && prototype.finish != NULL);

    Line writer = *target;
    while ((*writer.start++ = *prototype.start++) != '\0') {}
    target->finish = target->start + line_legth(prototype);
}

void lines_cat(Line *target, Line add)
{
    assert(target != NULL);
    assert(target->start != NULL && target->finish != NULL);
    assert(add.start != NULL && add.finish != NULL);

    Line writer = *target;
    while (writer.start <= target->finish)
    {
        writer.start++;
    }
    writer.start--;
    lines_copy(&writer, add);
    target->finish += line_legth(add);
}