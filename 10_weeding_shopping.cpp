#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include <string.h>

#define UNCOMPUTED INT32_MIN

#define MAX_NUM_MODELS 20
#define MAX_NUM_GARMENTS 20

int modelPrices[MAX_NUM_GARMENTS][MAX_NUM_MODELS];
bool gotAllGarments;

using namespace std;

int getGreatestCost(
    int line, int column, int numOfGarments, int moneySpent, int moneyToSpend)
{
    int myMoneySpent = moneySpent + modelPrices[line][column];
    // cout << modelPrices[line][column] << ", " <<lumn << myMoneySpent <<
    //     ", line: " << line << ", column: " << co endl;
    if (myMoneySpent > moneyToSpend) return moneySpent;
    if (line + 1 == numOfGarments) {
        gotAllGarments = true;
        /* cout << "###" << endl; */
        return myMoneySpent;
    }

    // if (line == 2) {
    //     cout << ">>" << endl;
    // }
    int cost, maxCost = myMoneySpent, numModels = modelPrices[line + 1][0];

    for (size_t j = 1; j <= numModels; j++)
    {
        cost = getGreatestCost(line + 1, j, numOfGarments, myMoneySpent, moneyToSpend);
        if (cost > maxCost) maxCost = cost;
    }

    // cout << "maxCost: " << maxCost << endl;
    return maxCost;
}

int main()
{
    // garment = vestuário
    int numOfTestCases, money, numOfGarments, numOfModels, maxCost, aux;
    cin >> numOfTestCases;

    for (size_t i = 0; i < numOfTestCases; i++)
    {
        cin >> money >> numOfGarments;
        // cout << "[" << money << ", " << numOfGarments << "]" << endl;
        for (size_t i = 0; i < numOfGarments; i++)
        {
            cin >> numOfModels;
            modelPrices[i][0] = numOfModels;

            for (size_t j = 1; j <= numOfModels; j++)
            {
                cin >> aux;
                modelPrices[i][j] = aux;
            }
        }

        gotAllGarments = false;
        numOfModels = modelPrices[0][0];
        maxCost = getGreatestCost(0, 1, numOfGarments, 0, money);

        for (size_t i = 2; i <= numOfModels; i++)
        {
            aux = getGreatestCost(0, i, numOfGarments, 0, money);
            if (aux > maxCost) maxCost = aux;
        }
        
        if (gotAllGarments) cout << maxCost << endl;
        else cout << "no solution" << endl;
    }
}
