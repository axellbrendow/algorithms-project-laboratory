#include <iostream>
#include <stdio.h>
#include <string.h>

#define MAX_NUM_LINES 100
#define MAX_NUM_COLUMNS 51

using namespace std;

int extractWords(char *line, int length)
{
    int pos = 0, j = 0;

    while (j < length && line[j] == ' ') j++;

    while (j < length && line[j] != ' ')
    {
        line[pos++] = line[j++];
    }

    while (j < length)
    {
        while (j < length && line[j] == ' ') j++;

        if (j < length && line[j] != ' ')
        {
            line[pos++] = ' ';

            do line[pos++] = line[j++];
            while (j < length && line[j] != ' ');
        }
    }

    line[pos] = '\0';

    return pos; // pos is the length of the string at this moment
}

int main()
{
    char lines[MAX_NUM_LINES][MAX_NUM_COLUMNS];
    char *line;
    int numLinhas, len, lineLength, maxLineLength;
    cin >> numLinhas;

    while (numLinhas > 0)
    {
        scanf("%s");
        maxLineLength = 0;

        for (size_t i = 0; i < numLinhas; i++)
        {
            line = lines[i];

            fgets(line, MAX_NUM_COLUMNS, stdin);
            len = strlen(line) - 1;
            
            lineLength = extractWords(line, len);
            maxLineLength = lineLength > maxLineLength ? lineLength : maxLineLength;
        }

        for (size_t i = 0; i < numLinhas; i++) printf("%*s\n", maxLineLength, lines[i]);
        puts("");
        
        cin >> numLinhas;
    }
}
