#ifndef LINESLIB_H
#define LINESLIB_H

#include "stdio.h"

//--------------------------------------------------------
//! Get length of the string. The string must end with '\0'
//!
//! \param [in] string line
//! \param [in] maximum_length maximum length of the line
//!
//! \return length of the line
//---------------------------------------------------------
int line_legth(const char *string, int maximum_length);

//---------------------------------------------------------
//! Find the first occurrence of a character in a string
//!
//! \param [in] string line
//! \param [in] target symbol
//! \param [in] maximum_length maximum length of the line
//!
//! \return pointer to the symbol
//---------------------------------------------------------
char *char_in_line(char *string, int target, int maximum_length);

//---------------------------------------------------------
//! Copy line to the line target. The length of the target must be at least the length of the copy line
//!
//! \param [in] target first line
//! \param [in] line second line
//!
//! \return pointer to the finished line
//---------------------------------------------------------
void lines_copy(char *target, const char *line);

//---------------------------------------------------------
//! Append line add to the end of line target. The length of the target must not be less than the total length of the
//! lines target and add
//!
//! \param [in] target first line
//! \param [in] add second line
//! \param [in] maximum_length
//!
//! \return pointer to the finished line
//---------------------------------------------------------
void lines_cat(char *target, const char *add);

//---------------------------------------------------------
//! Compare two lines by the first nCharacters characters
//!
//! \param [in] string1 first line
//! \param [in] string2 second line
//!
//! \return 0 (if lines are equal), 1 (if first line > second line), -1 (if second line < first line)
//---------------------------------------------------------
int lines_compare(const char *string1, const char *string2);

//---------------------------------------------------------
//! Compare two lines by the first nCharacters characters
//!
//! \param [in] string1 first line
//! \param [in] string2 second line
//!
//! \return 0 (if lines are equal), 1 (if first line > second line), -1 (if second line < first line)
//---------------------------------------------------------
int lines_compare_for_qsort(const void *string1, const void *string2);

//--------------------------------------------------------
//! Get size of the file
//!
//! \param file pointer to the file
//!
//! \return size of the file
//--------------------------------------------------------
int get_file_size(FILE *file);

//---------------------------------------------------------
//! Copy text of the file to the memory
//!
//! \param [in] file pointer to the file
//! \param [out] nLines pointer to number of lines in the file
//!
//! \return text of the tile
//---------------------------------------------------------
char *file_to_memory(FILE *file, int *nLines);

//---------------------------------------------------------
//! Split text into lines
//!
//! \param line text
//! \param nLines number of lines
//!
//! \return array of the lines
//---------------------------------------------------------
char **line_to_lines(char *text, int nLines);

//---------------------------------------------------------
//! sort massive of the lines
//!
//! \param lines array of the lines
//! \param left the left border of the sorted part of the array
//! \param right the кшпре border of the sorted part of the array
//---------------------------------------------------------
void lines_sort(char *lines[], int left, int right);

//---------------------------------------------------------
//! Swap 2 array elements
//!
//! \param lines array
//! \param fIndex index of the first element
//! \param sIndex index of the second element
//---------------------------------------------------------
void swap(char *lines[], int fIndex, int sIndex);

//----------------------------------------------------------
//! print lines from array to the file
//!
//! \param file pointer to the file
//! \param lines array of the lines
//! \param nLines number of lines
//----------------------------------------------------------
void f_print_lines(FILE *file, char *lines[], int nLines);

#endif //LINESLIB_H