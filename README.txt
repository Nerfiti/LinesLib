-----------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------

                                             LinesLib Project

-----------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------

This program has functions for reading lines from a file, operations on lines, printing them and a simple 
implementation of sorting strings from a file

-----------------------------------------------------------------------------------------------------------

Command line flags:

flag -t start the program with mode UNIT_TEST (Automatically standart tests).

flag -s start the program with mode SORT_FILE (The lines in the file will be sorted and placed in the 
file "output.txt") after this flag, you must enter the file name.

flag -f start the program with mode UNIT_TEST_OF_THE_FILE (Tests from file) after this flag 
you must enter the file name.

-----------------------------------------------------------------------------------------------------------

The test file should contain 6 objects in each line, separated by a space

First object - first line.

Second object - second line.

Third object - target symbol.

Fourth object - the position number of the target symbol in the first line.

Fifth object - the position number of the target symbol in the second line.

Sixth object - line resulting from concatenation first line and second line

Seventh object - length of the first line

Eighth object - length of the second line

Nints object - positive number (if line1 > line2), 0 (if line1 == line2) or 
negative number (if line1 < line2)

-----------------------------------------------------------------------------------------------------------

Documentation is in zip archive htmldoc/html/index.html.

-----------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------
