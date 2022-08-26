#ifndef FSTRLIB_H
#define FSTRLIB_H

#include "stdio.h"

//--------------------------------------------------------
//! Get string length
//!
//! \param [in] string line
//! \param [in] maximum_length maximum length of the line
//!
//! \return length of the line
//---------------------------------------------------------
int line_legth(const char *string, int maximum_length);

//---------------------------------------------------------
//! Compare two lines by the first nCharacters characters
//!
//! \param [in] string1 first line
//! \param [in] string2 second line
//! \param [in] nCharacters number of characters
//!
//! \return 0 (if lines are equal), 1 (if first line > second line), -1 (if second line < first line)
//---------------------------------------------------------
int lines_compare(const char *string1, const char *string2, int nCharacters);

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
//! Append line add to the end of line target
//!
//! \param [in] target first line
//! \param [in] add second line
//!
//! \return pointer to the finished line
//---------------------------------------------------------
char *lines_cat(char *target, const char *add, int maximum_length);

//--------------------------------------------------------
//! Get line of the file
//!
//! \param [in] file pointer to the file
//! \param [in] nChar_in_line number of characters in line
//!
//---------------------------------------------------------
char *f_read_line(FILE *file, int nChar_in_line);

//---------------------------------------------------------
//! Get number of lines in file
//!
//! \param filename name of the file
//!
//! \return number of lines
//---------------------------------------------------------
int f_get_nLines(FILE *file, int *nChar_in_lines, int maximum_nLines);

//---------------------------------------------------------
//! Get lines of the file
//!
//! \param [in] file pointer to the file
//! \param [in] nLines number of lines
//! \param [in] nChar_in_lines array with the number of characters in lines
//!
//! \return number of the lines
//---------------------------------------------------------
char **f_read_lines(FILE *file, int nLines, int *nChar_in_lines);

//---------------------------------------------------------
//! sort massive of the lines
//!
//! \param lines array of the lines
//! \param nLines number of lines
//! \param nChar_in_lines array with the number of characters in lines
//---------------------------------------------------------
void lines_sort(char *lines[], int nLines, int *nChar_in_lines);

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

#endif //FSTRLIB_H