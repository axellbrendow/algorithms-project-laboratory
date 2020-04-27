#include <iostream>
#include <vector>
#include <algorithm>

#define EDGE_DOESNT_EXIST -1
#define EDGE_EXIST 1
#define NOT_VISITED -1
#define VISITED 1

using namespace std;

typedef vector<int> EdgeVector;
typedef vector<EdgeVector> Graph;

Graph transpose(Graph& graph, int numOfVertices)
{
    Graph newGraph(numOfVertices, EdgeVector(numOfVertices, EDGE_DOESNT_EXIST));

    for (size_t i = 0; i < numOfVertices; i++)
        for (size_t j = 0; j < numOfVertices; j++)
            newGraph[i][j] = graph[j][i];
            
    return newGraph;
}

int numOfConnections;

void visitNeighbors(int vertex, Graph& graph, int numOfVertices, vector<int>& visitedVertices)
{
    visitedVertices[vertex] = VISITED;
    EdgeVector& edgeVector = graph[vertex];

    for (size_t i = 0; i < numOfVertices; i++)
    {
        if (edgeVector[i] == EDGE_EXIST && visitedVertices[i] == NOT_VISITED)
        {
            visitedVertices[i] = VISITED;
            visitNeighbors(i, graph, numOfVertices, visitedVertices);
        }
    }
}

bool isGraphConnected(Graph& graph, int numOfVertices, int initialVertex = 0)
{
    vector<int> visitedVertices(numOfVertices, NOT_VISITED);

    visitNeighbors(initialVertex, graph, numOfVertices, visitedVertices);
    
    return find(visitedVertices.begin(), visitedVertices.end(), NOT_VISITED) == visitedVertices.end();
}

int main()
{
    int numOfIntersections, numOfStreets, intersection0, intersection1, street_type;
    cin >> numOfIntersections >> numOfStreets;

    while (!cin.eof() && (numOfIntersections != 0 || numOfStreets != 0))
    {
        Graph graph(numOfIntersections, EdgeVector(numOfIntersections, EDGE_DOESNT_EXIST));

        for (size_t i = 0; i < numOfStreets; i++)
        {
            cin >> intersection0 >> intersection1 >> street_type;
            intersection0 -= 1;
            intersection1 -= 1;
            graph[intersection0][intersection1] = EDGE_EXIST;
            if (street_type == 2) graph[intersection1][intersection0] = EDGE_EXIST;
        }

        Graph transposeGraph = transpose(graph, numOfIntersections);
        bool isOriginalGraphConnected = isGraphConnected(graph, numOfIntersections);
        bool isTransposeGraphConnected = isGraphConnected(transposeGraph, numOfIntersections);
        cout << (isOriginalGraphConnected && isTransposeGraphConnected ? 1 : 0) << endl;
        cin >> numOfIntersections >> numOfStreets;
    }
}
