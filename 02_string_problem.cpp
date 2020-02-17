#include <iostream>
#include <stdio.h>
#include <string.h>
#include <windows.h>

using namespace std;

int main()
{
    char linhas[100][51];
    int numLinhas, len;
    cin >> numLinhas;

    while (numLinhas > 0)
    {
        scanf("%s");

        for (size_t i = 0; i < numLinhas; i++)
        {
            fgets(linhas[i], 51, stdin);
            len = strlen(linhas[i]) - 1;

            for (size_t j = 0; j < len; j++)
            {
                //
            }
        }
        
        cin >> numLinhas;
    }
}
