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

int graph[MAX_NUM_CITIES][MAX_NUM_CITIES];

using namespace std;

void printGraph(int numCities)
{
    for (size_t i = 0; i < numCities; i++)
    {
        for (size_t j = 0; j < numCities; j++) printf("%7d ", graph[i][j]);
        cout << endl;
    }
}

void clearGraph(int numCities)
{
    for (size_t i = 0; i < numCities; i++)
        for (size_t j = 0; j < numCities; j++)
            graph[i][j] = INFTY;

    for (size_t i = 0; i < numCities; i++) graph[i][i] = 0;
}

void floydWarshall(int numCities)
{
    for (size_t k = 0; k < numCities; k++)
        for (size_t i = 0; i < numCities; i++)
            for (size_t l = 0; l < numCities; l++)
                graph[i][l] = min(graph[i][l], graph[i][k] + graph[k][l]);
}

/** Dynamic Programming approach to gas station problem */
int gasStationDP(
    int vertex,
    int numCities,
    int capacity,
    int costsPerLiterOfFuel[],
    vector<vector<int>> &startingFuelsForAllVertices,
    vector<vector<int>> &memoTable)
{
    auto costPerLiterOfFuelForMe = costsPerLiterOfFuel[vertex];
    auto &startingFuelsForMe = startingFuelsForAllVertices[vertex];
    int cost, minCost = INT32_MAX;

    for (size_t i = 0; i < startingFuelsForMe.size(); i++)
    {
        auto startingFuelForMe = startingFuelsForMe[i];
        cost = memoTable[vertex][startingFuelForMe];
        if (cost == UNDEFINED)
        {
            for (size_t j = vertex + 1; j < numCities; j++)
            {
                if (j == vertex) continue;
                if (costsPerLiterOfFuel[j] > costPerLiterOfFuelForMe)
                {
                    startingFuelsForAllVertices[j].push_back(capacity - graph[vertex][j]);
                    cost = gasStationDP(j, numCities, capacity, costsPerLiterOfFuel,
                        startingFuelsForAllVertices, memoTable)
                        + (capacity - startingFuelForMe) * costPerLiterOfFuelForMe;
                }

                else if (startingFuelForMe <= graph[vertex][j] || j == numCities - 1)
                    cost = gasStationDP(j, numCities, capacity, costsPerLiterOfFuel,
                        startingFuelsForAllVertices, memoTable)
                        + (graph[vertex][j] - startingFuelForMe) * costPerLiterOfFuelForMe;
            }
        }
        // printf("cost = %d, vertex = %d, startingFuelForMe = %d\n", cost, vertex, startingFuelForMe);
        if (cost < minCost) minCost = cost;
    }

    return minCost;
}

void getStartingFuelsForAllVertices(
    vector<vector<int>> &startingFuelsForAllVertices,
    int numCities,
    int capacity,
    int costsPerLiterOfFuel[]
)
{
    for (size_t vertex = 0; vertex < numCities - 1; vertex++)
    {
        auto vertexCostPerLiterOfFuel = costsPerLiterOfFuel[vertex];
        auto &startingFuels = startingFuelsForAllVertices[vertex];

        // Our car can start with 0 of fuel on all vertices except first.
        if (vertex == 0) startingFuels.push_back(capacity);
        else startingFuels.push_back(0);

        for (size_t i = 0; i < numCities; i++)
            if (costsPerLiterOfFuel[i] < vertexCostPerLiterOfFuel
                && graph[i][vertex] <= capacity)
            {
                startingFuels.push_back(capacity - graph[i][vertex]);
            }
    }
    startingFuelsForAllVertices[numCities - 1].push_back(0);
}

int main()
{
    int numCities, numRoads, capacity;
    cin >> numCities >> numRoads >> capacity;

    while (numCities != 0 || numRoads != 0 || capacity != 0)
    {
        clearGraph(numCities);

        for (size_t i = 0; i < numRoads; i++)
        {
            int startingVertex, endingVertex, weight;
            cin >> startingVertex >> endingVertex >> weight;
            graph[startingVertex - 1][endingVertex - 1] =
                graph[endingVertex - 1][startingVertex - 1] = weight;
        }

        /** Each city price per liter */
        int costsPerLiterOfFuel[numCities];

        for (size_t i = 0; i < numCities; i++)
            cin >> costsPerLiterOfFuel[i];

        floydWarshall(numCities); // Use floyd to create complete graph
        if (graph[0][numCities - 1] == INFTY)
        {
            cout << "-1" << endl;
            cin >> numCities >> numRoads >> capacity;
            continue;
        }

        vector<vector<int>> startingFuelsForAllVertices(numCities, vector<int>());
        getStartingFuelsForAllVertices(startingFuelsForAllVertices,
            numCities, capacity, costsPerLiterOfFuel);

        vector<vector<int>> memoTable(numCities, vector<int>(capacity + 1, UNDEFINED));
        memoTable[numCities - 1][0] = 0;

        cout << gasStationDP(0, numCities, capacity, costsPerLiterOfFuel,
            startingFuelsForAllVertices, memoTable) << endl;
        
        cin >> numCities >> numRoads >> capacity;
    }
}
