#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <math.h>
#include <stdio.h>

/*
REFERENCES:

https://www.urionlinejudge.com.br/judge/pt/problems/view/1529
https://www.udebug.com/URI/1529
https://csacademy.com/app/graph_editor/
https://cs.stackexchange.com/questions/25906/understanding-an-algorithm-for-the-gas-station-problem?noredirect=1&lq=1
https://cs.stackexchange.com/questions/115930/grokking-pseudo-code-for-solution-to-gas-station-problem?noredirect=1&lq=1
http://www.cs.umd.edu/projects/gas/gas-station.pdf
https://dl.acm.org/doi/pdf/10.1145/1978782.1978791
KLEITOS PAPADOPOULOS AND DEMETRES CHRISTOFIDES. A FAST ALGORITHM FOR THE GAS STATION PROBLEM
*/

#define INFTY 1000000
#define UNDEFINED -1
#define MAX_NUM_CITIES 10

using namespace std;

int graph[MAX_NUM_CITIES][MAX_NUM_CITIES];
int numCities;
int U;
int c[MAX_NUM_CITIES];
vector<vector<int>> memoTable;

void printGraph()
{
    for (size_t i = 0; i < numCities; i++)
    {
        for (size_t j = 0; j < numCities; j++) printf("%7d ", graph[i][j]);
        cout << endl;
    }
}

void clearGraph()
{
    for (size_t i = 0; i < numCities; i++)
        for (size_t j = 0; j < numCities; j++)
            graph[i][j] = INFTY;

    for (size_t i = 0; i < numCities; i++) graph[i][i] = 0;
}

void floydWarshall()
{
    for (size_t k = 0; k < numCities; k++)
        for (size_t i = 0; i < numCities; i++)
            for (size_t l = 0; l < numCities; l++)
                graph[i][l] = min(graph[i][l], graph[i][k] + graph[k][l]);
}

int gasStationDP(int u, int g)
{
    if (u == numCities - 1) g = 0;
    int cost = memoTable[u][g], minCost = INT32_MAX;
    
    if (cost == UNDEFINED)
        for (size_t v = u + 1; v < numCities; v++)
        {
            cost = INT32_MAX;
            if (graph[u][v] > U) continue;
            if (c[v] > c[u])
            {
                // printf("->u: '%d', c[u]: '%3d',\tv: '%d',\tc[v]: '%2d',  d[u][v]: '%2d',  g: '%3d',  refuel: '%3d',\tminCost: '%3d'\n", u, c[u], v, c[v], graph[u][v], g, U - g, minCost);
                cost = gasStationDP(v, U - graph[u][v]) + (U - g) * c[u];
            }

            else if (g >= graph[u][v])
            {
                // printf("->u: '%d', c[u]: '%3d',\tv: '%d',\tc[v]: '%2d',  d[u][v]: '%2d',  g: '%3d',  refuel: '%3d',\tminCost: '%3d'\n", u, c[u], v, c[v], graph[u][v], g, 0, minCost);
                cost = gasStationDP(v, g - graph[u][v]);
            }

            else
            {
                int refuel = graph[u][v] - g;
                // printf("->u: '%d', c[u]: '%3d',\tv: '%d',\tc[v]: '%2d',  d[u][v]: '%2d',  g: '%3d',  refuel: '%3d',\tminCost: '%3d'\n", u, c[u], v, c[v], graph[u][v], g, refuel, minCost);
                cost = gasStationDP(v, 0) + refuel * c[u];
            }

            if (cost >= 0 && cost < minCost) minCost = cost;
            // printf("<-u: '%d', c[u]: '%3d',\tv: '%d',\tc[v]: '%2d',  d[u][v]: '%2d',  g: '%3d',  \t\tminCost: '%3d'\n", u, c[u], v, c[v], graph[u][v], g, minCost);
        }

    else minCost = cost;
    return memoTable[u][g] = minCost;
}

int main()
{
    int numRoads;
    cin >> numCities >> numRoads >> U;
    // int i = 0;
    while (numCities != 0 || numRoads != 0 || U != 0)
    {
        // printf("#### CASE %d, numCities: %d, numRoads: %d, capacity: %d ####\n", i++, numCities, numRoads, U);
        clearGraph();

        for (size_t i = 0; i < numRoads; i++)
        {
            int startingVertex, endingVertex, weight;
            cin >> startingVertex >> endingVertex >> weight;
            graph[startingVertex - 1][endingVertex - 1] =
                graph[endingVertex - 1][startingVertex - 1] = weight;
        }

        /** Each city price per liter */
        for (size_t i = 0; i < numCities; i++) cin >> c[i];

        floydWarshall(); // Use floyd to create complete graph
        // printGraph();
        if (graph[0][numCities - 1] == INFTY) // There's no path to the last vertex
        {
            cout << "-1" << endl;
            cin >> numCities >> numRoads >> U;
            continue;
        }

        memoTable = vector<vector<int>>(numCities, vector<int>(U + 1, UNDEFINED));
        memoTable[numCities - 1][0] = 0;

        int cost = gasStationDP(0, U);
        cout << (cost == INT32_MAX ? -1 : cost) << endl;
        
        cin >> numCities >> numRoads >> U;
    }
}
