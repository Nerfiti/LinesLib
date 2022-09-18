#include "assert.h"
#include "ctype.h"
#include "linesLib.h"
#include "malloc.h"
#include <sys/stat.h>


const unsigned long int MAXIMUM_LENGTH_OF_THE_LINE = 4294967295;
const void *JUST_FREE_PTR = "JUST_FREE";

void SortFile(const char *filename, bool reverse, bool backsort)
{
    Text file_text = {};

    //Open the file with text
    FILE *file = fopen(filename, "r");
    if (file == nullptr)
    {
        printf("Error opening the file.");
        return;
    }

    //Read file and copy it to memory
    printf("Reading the file...\n");
    file_to_memory(file, &file_text);
    if (file_text.content == nullptr)
    {
        printf("File reading error.\n");
        return;
    }
    printf("The file has been read.\n\n");

    //Split the text of the file into lines
    printf("Splitting the text of the file into lines...\n");
    text_to_lines(&file_text);
    printf("The text has been splitting.\n\n");

    //Sort text of the file
    printf("Sorting...\n");
    lines_qsort(file_text.lines, 0, file_text.nLines - 1, reverse, backsort);
    printf("The file has been sorted.\n\n");

    assert(fclose(file) != EOF);

    //Print sorted text to a file "Output.txt"
    FILE *out_file = fopen("./Output.txt", "w");
    if (out_file == nullptr)
    {
        printf("Error opening the file.\n");
        return;
    }

    f_print_lines(out_file, file_text.lines, file_text.nLines);

    FreeBuff(&file_text);

    assert(fclose(out_file) != EOF);
}

int get_file_size(FILE *file)
{
    struct stat file_stat = {};
    fstat(fileno(file), &file_stat);
    return file_stat.st_size;
}

void file_to_memory(FILE *file, Text *text)
{
    assert(file != nullptr);
    assert(text != nullptr);

    text->content = (char *)calloc(get_file_size(file), sizeof(char));
    assert(text->content != nullptr);

    char *writer = text->content;
    bool was_alpha = false;
    char *start_line = text->content;

    while ((*writer = getc(file)) != EOF)
    {
        char curSymbol = *writer;
        if (isalpha(curSymbol) && curSymbol != 'I' && curSymbol != 'X' && curSymbol != 'V' && curSymbol != 'L')
        {
            was_alpha = true;
        }
        if (curSymbol == '\n')
        {
            if (was_alpha)
            {
                (text->nLines)++;
                was_alpha = false;
                start_line = writer + 1;
            }
            else
            {
                writer = start_line - 1;
            }
        }
        writer++;
    }
    (text->nLines)++;
    *writer = '\0';
}

void text_to_lines(Text *text)
{
    assert(text != nullptr);
    assert(text->content != nullptr);
    char *reader = text->content;

    int nLines = text->nLines;
    text->lines = (Line *)calloc(text->nLines, sizeof(Line));
    Line *start_array = text->lines;
    assert(text->lines != nullptr);

    text->lines->start = reader;
    reader++;
    int line_index = 1;
    while (*reader != '\0' && line_index <= nLines)
    {
        if (*reader == '\n')
        {
            *reader = '\0';
            text->lines->finish = reader;
            text->lines++;
            text->lines->start = reader + 1;
            line_index++;
        }
        reader++;
    }
    *reader = '\0';
    text->lines->finish = reader;
    text->lines = start_array;
}

void lines_qsort(Line *lines, int left, int right, bool reverse, bool backsort)
{
    assert(lines != nullptr);

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
    assert(string1.start != nullptr && string1.finish != nullptr);
    assert(string2.start != nullptr && string2.finish != nullptr);

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
    assert(lines != nullptr);

    Line temp = lines[fIndex];
    lines[fIndex] = lines[sIndex];
    lines[sIndex] = temp;
}

void f_print_lines(FILE *file, Line *lines, int nLines)
{
    assert(file != nullptr);
    assert(lines != nullptr);

    for (int i = 0; i < nLines; i++)
    {
        assert(lines[i].start != nullptr);

        fprintf(file, "%s\n", lines[i].start);
    }
}

Line string_to_Line(const char *string)
{
    assert(string != nullptr);

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
    assert(string.start != nullptr);
    assert(string.finish != nullptr);

    return string.finish - string.start;
}

char *char_in_line(Line string, char target)
{
    assert(string.start != nullptr);
    assert(string.finish != nullptr);

    for (const char *search = string.start;
        *search != '\0' && search - string.start < MAXIMUM_LENGTH_OF_THE_LINE;
         search++)
    {
        if (*search == target)
        {
            return (char *)search;
        }
    }
    return nullptr;
}

void lines_copy(Line *target, Line prototype)
{
    assert(target != nullptr);
    assert(target->start != nullptr && target->finish != nullptr);
    assert(prototype.start != nullptr && prototype.finish != nullptr);

    Line writer = *target;
    while ((*writer.start++ = *prototype.start++) != '\0') {}
    target->finish = target->start + line_legth(prototype);
}

void lines_cat(Line *target, Line add)
{
    assert(target != nullptr);
    assert(target->start != nullptr && target->finish != nullptr);
    assert(add.start != nullptr && add.finish != nullptr);

    Line writer = *target;
    while (writer.start <= target->finish)
    {
        writer.start++;
    }
    writer.start--;
    lines_copy(&writer, add);
    target->finish += line_legth(add);
}

void FreeBuff(Text *text)
{
    assert(text != nullptr);
    assert(text->content != nullptr);
    assert(text->lines != nullptr);

    if(text->content == JUST_FREE_PTR || text->lines == JUST_FREE_PTR)
    {
        printf("Calling the FreeBuff function again. Memory has not been released");
        return;
    }
    free(text->content);
    free(text->lines);
    text->content = (char*)JUST_FREE_PTR;
    text->lines = (Line *)JUST_FREE_PTR;
}