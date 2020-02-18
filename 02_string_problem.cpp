#include <iostream>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_NUM_LINES 100
#define MAX_NUM_COLUMNS 51

using namespace std;

int extractWords(char *line, int length)
{
    int pos = 0, j = 0;

    while (line[j] == ' ') j++;

    if (j < length)
    {
        line[pos++] = line[j++];
    }

    for (; j < length; j++)
    {
        while (line[j] == ' ') j++;

        if (j < length)
        {
            line[pos++] = ' ';
            line[pos++] = line[j];
        }
    }

    line[pos] = '\0';

    return pos;
}

int main()
{
    char linhas[MAX_NUM_LINES][MAX_NUM_COLUMNS];
    char *line;
    int lineLengths[MAX_NUM_LINES];
    int numLinhas, len, maxLineLength = 0;
    cin >> numLinhas;

    while (numLinhas > 0)
    {
        scanf("%s");

        for (size_t i = 0; i < numLinhas; i++)
        {
            line = linhas[i];

            fgets(line, MAX_NUM_COLUMNS, stdin);
            len = strlen(line) - 1;
            puts("\n----- BEFORE -------\n\n");
            puts(line);
            
            lineLengths[i] = extractWords(line, len);
            puts("\n----- AFTER -------\n\n");
            puts(line);
            maxLineLength = lineLengths[i] > maxLineLength ? lineLengths[i] : maxLineLength;
        }
        
        cin >> numLinhas;
    }
}
