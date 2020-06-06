#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <bits/stdc++.h>

/*
REFERENCES:

https://www.urionlinejudge.com.br/judge/pt/problems/view/1034
http://prorum.com/?qa=3250/problema-troco-resolve-abordagem-natural-sempre-funciona
*/

using namespace std;

#define MAX_NUM_BLOCKS 25

int blocksLength[MAX_NUM_BLOCKS];
int numBlocks;
int lengthToGet;

int greedy()
{        
    sort(blocksLength, blocksLength + numBlocks, greater<int>());

    int minNumBlocksNeeded = 0;
    for (size_t i = 0; i < numBlocks; i++)
    {
        while (blocksLength[i] <= lengthToGet)
        {
            minNumBlocksNeeded++;
            lengthToGet -= blocksLength[i];
        }
    }
    return minNumBlocksNeeded;
}

int dynamic()
{
    int minBlocksForLength[lengthToGet + 1];
    fill(minBlocksForLength, minBlocksForLength + lengthToGet + 1, 0);

    for (size_t currLengthToGet = 1; currLengthToGet <= lengthToGet; currLengthToGet++)
    {
        int minNumBlocks = currLengthToGet;

        for (size_t i = 1; i < numBlocks; i++)
        {
            if (currLengthToGet >= blocksLength[i])
            {
                if (minBlocksForLength[currLengthToGet - blocksLength[i]] + 1 < minNumBlocks)
                {
                    minNumBlocks = minBlocksForLength[currLengthToGet - blocksLength[i]] + 1;
                }
            }
        }

        minBlocksForLength[currLengthToGet] = minNumBlocks;
    }
    
    return minBlocksForLength[lengthToGet];
}

int main()
{
    int numTests;
    cin >> numTests;
    for (size_t i = 0; i < numTests; i++)
    {
        cin >> numBlocks >> lengthToGet;

        for (size_t i = 0; i < numBlocks; i++) cin >> blocksLength[i];

        // cout << greedy() << endl;
        cout << dynamic() << endl;
    }
}
