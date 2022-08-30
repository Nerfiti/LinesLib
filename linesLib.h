#ifndef LINESLIB_H
#define LINESLIB_H

#include "stdio.h"
#include "sys/time.h"

struct Line{
    char *start = NULL;
    char *finish = NULL;
};

//-----------------------------------------------------------
//! Sort lines from the file and print it to the "Output.txt"
//!
//! \param [in] filename the name of the file
//! \param [in] reverse whether to sort the strings in reverse lexicographic order
//! \param [in] backsort whether to sort lines from the end
//-----------------------------------------------------------
void SortFile(const char *filename, bool reverse, bool backsort);

//-----------------------------------------------------------
//! Get size of the file
//!
//! \param [in] file pointer to the file
//!
//! \return size of the file
//-----------------------------------------------------------
int get_file_size(FILE *file);

//-----------------------------------------------------------
//! Copy text of the file to the memory. The user
//! guarantees that the entire text will fit into memory
//! according to this pointer
//!
//! \param [in] file pointer to the file
//! \param [out] nLines pointer to number of lines in the file
//! \param [out] file_text pointer to the place for the text of the file
//-----------------------------------------------------------
void file_to_memory(FILE *file, int *nLines, char *file_text);

//-----------------------------------------------------------
//! Split text into lines. The user guarantees that
//! the size of the array allows you to put
//! all the lines there
//!
//! \param [in] line the text to be split
//! \param [in] nLines number of lines
//! \param [out] lines array of the lines
//-----------------------------------------------------------
void line_to_lines(char *text, int nLines, Line *lines);

//-----------------------------------------------------------
//! Sort massive of the lines.
//!
//! \param [in, out] lines array of the lines
//! \param [in] left the left border of the sorted part of the array
//! \param [in] right the right border of the sorted part of the array
//! \param [in] reverse whether to sort the strings in reverse lexicographic order
//! \param [in] backsort whether to sort lines from the end
//-----------------------------------------------------------
void lines_qsort(Line *lines, int left, int right, bool reverse, bool qsort);

//-----------------------------------------------------------
//! Compare two lines by the first nCharacters characters
//!
//! \param [in] string1 first line
//! \param [in] string2 second line
//! \param [in] reverse whether to sort the strings in reverse lexicographic order
//! \param [in] backsort whether to sort lines from the end
//!
//! \return 0 (if lines are equal), 1 (if first line > second line), -1 (if second line < first line)
//-----------------------------------------------------------
int lines_compare(Line string1, Line string2, bool reverse, bool backsort);

//-----------------------------------------------------------
//! Swap 2 array elements
//!
//! \param [in, out] lines array
//! \param [in] fIndex index of the first element
//! \param [in] sIndex index of the second element
//-----------------------------------------------------------
void swap(Line *lines, int fIndex, int sIndex);

//-----------------------------------------------------------
//! print lines from array to the file
//!
//! \param [in] file pointer to the file
//! \param [in] lines array of the lines
//! \param [in] nLines number of lines
//-----------------------------------------------------------
void f_print_lines(FILE *file, Line *lines, int nLines);

//-----------------------------------------------------------
//! Сonvert type (char *) to type (Line)
//! The string must end with '\0'
//!
//! \param [in] string line of type (char *)
//!
//! \return line of type (Line)
//-----------------------------------------------------------
Line string_to_Line(const char *string);

//-----------------------------------------------------------
//! Get length of the string.
//!
//! \param [in] string line
//!
//! \return length of the line
//-----------------------------------------------------------
unsigned long int line_legth(const Line string);

//-----------------------------------------------------------
//! Find the first occurrence of a character in a string
//!
//! \param [in] string line
//! \param [in] target target symbol
//!
//! \return pointer to the symbol
//-----------------------------------------------------------
char *char_in_line(Line string, char target);

//-----------------------------------------------------------
//! Copy line prototype to the line target. The length of the target must be at least the length of the copy line
//!
//! \param [in] target first line
//! \param [in] prototype second line
//-----------------------------------------------------------
void lines_copy(Line *target, Line prototype);

//-----------------------------------------------------------
//! Append line add to the end of line target. The length of the target must not be less than the total length of the
//! lines target and add
//!
//! \param [in] target first line
//! \param [in] add second line
//-----------------------------------------------------------
void lines_cat(Line *target, Line add);

//-----------------------------------------------------------
//! Get the difference between start and finish in
//! milliseconds
//!
//! \param [in] start start timer
//! \param [in] finish stop timer
//!
//! \return milliseconds between start ans finish
//-----------------------------------------------------------
long deltaT(timeval start, timeval finish);

#endif //LINESLIB_H