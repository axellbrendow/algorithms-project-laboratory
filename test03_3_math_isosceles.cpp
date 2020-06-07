#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <bits/stdc++.h>

/*
REFERENCES:

https://www.urionlinejudge.com.br/judge/pt/problems/view/2243
*/

using namespace std;

#define MAX_WALL_COLUMNS 50000

int columnsHeight[MAX_WALL_COLUMNS];
int numColumns;

bool isValidSolution(int index, int height)
{
    if (index + height > numColumns) return false;

    for (size_t i = 0; i < height; i++)
        if (columnsHeight[index + i] < height - i) return false;
    
    return true;
}

int greedy()
{
    int height = 1, maxHeight = INT32_MIN;

    for (size_t i = 0; i < numColumns; i++)
    {
        while (!isValidSolution(i, height)) height--;
        if (height > maxHeight) maxHeight = height;
        height++;
    }

    return maxHeight;
}

int main()
{
    cin >> numColumns;
    for (size_t i = 0; i < numColumns; i++) cin >> columnsHeight[i];
    cout << greedy() << endl;
}
