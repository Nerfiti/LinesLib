#include "UnitTests.h"

bool stdLinesLibTest()
{
    const int numberOfTests = 3;
    char str1[] = "Hello",
         str2[] = "HEllO",
         str3[] = "It's",
         str4[] = "HelloHEllO",
         str5[] = "HelloIt's",
         str6[] = "It'sHEllO",
         str7[] = "Hello",
         str8[] = "It's",
         str9[] = "HEllO";
    Test_case stdCases[numberOfTests] = {
        {str1, str2, 'o', 5, 0, str4, 5, 5, 1},
        {str7, str3, 's', 0, 4, str5, 5, 4, -1},
        {str8, str9, 'l', 0, 3, str6, 4, 5, 1}
    };
    return LinesLibTest(stdCases, numberOfTests);
}

bool LinesLibTest(int num, char *line1, char *line2, char target, int targetPos1, int targetPos2,
                  char *catlines, unsigned long int len1, unsigned long int len2, int comparationIndex)
{
    bool OK = true;
    Line Line1 = string_to_Line(line1);
    Line Line2 = string_to_Line(line2);
    Line Catlines = string_to_Line(catlines);

    // char_in_line testing
    char *ptr1 = char_in_line(Line1, target);
    char *ptr2 = char_in_line(Line2, target);
    long long posfact1 = ptr1 - Line1.start + 1;
    long long posfact2 = ptr2 - Line2.start + 1;
    printf("Test %d\n", num);
    if (Test_char_in_line(Line1, target, targetPos1) && Test_char_in_line(Line2, target, targetPos2))
    {
        printf("testing of the function \"char_in_line\" was successful.\n");
    }
    else
    {
        printf("\"char_in_line\" function testing failed. Output: %lld, %lld. Expected: %d, %d\n",
               posfact1, posfact2, targetPos1, targetPos2);
        OK = false;
    }

    // lines_compare testing
    if ((lines_compare(Line1, Line2, false, false) == 0 && comparationIndex == 0) ||
        (lines_compare(Line1, Line2, false, false)) * comparationIndex > 0)
    {
        printf("testing of the function \"lines_compare\" was successful.\n");
    }
    else
    {
        printf("\"lines_compare\" function testing failed. Output: %d. Expected: %d\n",
               lines_compare(Line1, Line2, false, false), comparationIndex);
        OK = false;
    }

    //line_length testing
    if (line_legth(Line1) == len1 && line_legth(Line2) == len2)
    {
        printf("testing of the function \"line_length\" was successful.\n");
    }
    else
    {
        printf("\"line_length\" function testing failed. Output: %lu, %lu. Expected: %lu, %lu\n",
               line_legth(Line1), line_legth(Line2), len1, len2);
        OK = false;
    }

    // lines_cat testing. It works correctly when the lines_compare function works correctly.
    lines_cat(&Line1, Line2);
    if (lines_compare(Line1, Catlines, false, false) == 0)
    {
        printf("testing of the function \"lines_cat\" was successful.\n\n\n");
    }
    else
    {
        printf("\"lines_cat\" function testing failed. Output: %s. Expected: %s\n\n\n",
               Line1.start, Catlines.start);
        OK = false;
    }
    return OK;
}

bool LinesLibTest(int num, Test_case testCase)
{
    return LinesLibTest(num, testCase.line1, testCase.line2, testCase.target, testCase.targetPos1, testCase.targetPos2,
                        testCase.catlines, testCase.len1, testCase.len2, testCase.comarationIndex);
}

bool LinesLibTest(Test_case testCase[], int count)
{
    bool allTests;
    int nTests = 0,
        nPassedTests = 0;
    for (int i = 0; i < count; i++)
    {
        if (!LinesLibTest(i + 1, testCase[i]))
        {
            allTests = false;
            nPassedTests--;
        }

        nPassedTests++;
        nTests++;
    }
    printf("LinesLibTest: %d/%d tests had been passed.\n", nPassedTests, nTests);
    return allTests;
}

bool LinesLibTest(const char *filename)
{
    bool allTests = true;
    const int max_len = 101;
    char line1[max_len] = {},
         line2[max_len] = {},
         target = 0,
         catlines[2*max_len] = {};
    int targetPos1 = 0,
        targetPos2 = 0,
        len1 = 0,
        len2 = 0,
        comarationIndex = 0,
        flag = 0,
        numberOfTests = 0,
        numberOfPassedTests = 0;
    FILE *file = fopen(filename, "r");//!
    if (file == NULL)
    {
        printf("Error opening the file: \"%s\".\n", filename);
        return false;
    }

    while ((flag = fscanf(file, "%100s %100s %c %d %d %s %d %d %d", line1, line2,
                          &target, &targetPos1, &targetPos2, catlines,
                          &len1, &len2, &comarationIndex)) != EOF)
    {
        numberOfTests++;
        if (flag < 9)
        {
            printf("Error in test %d: the format does not match the sample\n", numberOfTests);
            allTests = false;
            skipLine(file);
            continue;
        }
        if (!LinesLibTest(numberOfTests, line1, line2,
                          target, targetPos1, targetPos2, catlines,
                          len1, len2, comarationIndex))
        {
            numberOfPassedTests--;
            allTests = false;
        }
        skipLine(file);
        numberOfPassedTests++;
    }

    printf("LinesLibTest: %d/%d tests had been passed.\n", numberOfPassedTests, numberOfTests);
    fclose(file);
    return allTests;
}

bool Test_char_in_line(Line line, char target, int targetPos)
{
    char *ptr = char_in_line(line, target);
    if (ptr == NULL && targetPos == 0)
    {
        return true;
    }
    if ((ptr == NULL && targetPos != 0) || (ptr != NULL && targetPos == 0))
    {
        return false;
    }
    if (ptr - line.start == targetPos - 1)
    {
        return true;
    }
    return false;
}

void skipLine(FILE *file)
{
    int ch = 0;
    while ((ch = getc(file)) != EOF && ch != '\n') {}
}