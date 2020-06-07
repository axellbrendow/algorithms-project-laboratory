#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>
#include <limits>
#include <algorithm>
#include <bits/stdc++.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define MAX_BOARD_SIZE 100
#define MAX_NUM_VERTICES (MAX_BOARD_SIZE * MAX_BOARD_SIZE)
#define TURRET 'T'
#define PAWN 'X'
#define EMPTY '.'

bool graph[MAX_NUM_VERTICES][MAX_NUM_VERTICES];
char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int boardSize;
int numVertices;

int findPawnColumn(int line, int startingColumn)
{
    int pawnColumn = startingColumn;
    while (pawnColumn < boardSize && board[line][pawnColumn] != PAWN)
        pawnColumn++;
    return pawnColumn;
}

int findPawnLine(int startingLine, int column)
{
    int pawnLine = startingLine;
    while (pawnLine < boardSize && board[pawnLine][column] != PAWN)
        pawnLine++;
    return pawnLine;
}

int getVertexDegree(int vertex)
{
    int degree = 0;
    for (size_t j = 0; j < numVertices; j++)
        if (graph[vertex][j]) degree++;
    return degree;
}

typedef struct {
    size_t index;
    int degree;
} Vertex;

void removeNeighboors(int vertex, vector<Vertex> &vertices)
{
    for (size_t i = 0; i < numVertices; i++)
        if (graph[vertex][i]) // Check if the vertex `i` is a neighboor of `vertex`
        {
            graph[vertex][i] = graph[i][vertex] = false;

            for (size_t j = 0; j < numVertices; j++) // Remove all edges from `i`
            {
                if (graph[j][i]) // Check edge with neighboors of `i`
                {
                    auto neighboorItr = find_if(vertices.begin(), vertices.end(),
                        [j](Vertex &vertexObj){
                            return vertexObj.index == j;
                        }
                    );
                    if (neighboorItr != vertices.end()) neighboorItr->degree--;
                    graph[i][j] = graph[j][i] = false;
                }
            }
            
            vertices.erase(find_if(vertices.begin(), vertices.end(),
                [i](Vertex &vertexObj) {
                    return vertexObj.index == i;
                }
            ));
        }
}

void initVariables(vector<Vertex> &vertices, int &indexSmallestDegree)
{
    int degree, smallestDegree = INT32_MAX;
    // Get all vertices that represent an empty position in the board
    for (size_t i = 0; i < numVertices; i++)
    {
        int line = i / boardSize;
        int column = i % boardSize;
        if (board[line][column] == EMPTY)
        {
            degree = getVertexDegree(i);
            if (degree < smallestDegree)
            {
                smallestDegree = degree;
                indexSmallestDegree = vertices.size();
            }
            vertices.push_back(Vertex{i, degree});
        }
    }
}

void getRemainingVertices(vector<Vertex> &vertices, vector<int> &independentVertices)
{
    vector<Vertex>::iterator vertexItr;
    // If there are remaining vertices in the `vertices` vector, these vertices
    // belong to the maximum independent set
    while (!vertices.empty())
    {
        vertexItr = vertices.begin();
        independentVertices.push_back(vertexItr->index);
        vertices.erase(vertexItr);
    }
}

void printGraph()
{
    cout << "GRAPH" << endl;
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++) cout << graph[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

int getMaxNumTurrets_IndependentSet()
{
    // printBoard(0);
    // printGraph();
    vector<Vertex> vertices;
    vertices.reserve(numVertices);
    int indexSmallestDegree = -1;
    initVariables(vertices, indexSmallestDegree);
    if (indexSmallestDegree == -1) return 0;

    int vertex;
    auto smallestVertexItr = vertices.begin() + indexSmallestDegree;
    vector<int> independentVertices; // To store the maximum independent set of vertices.
    independentVertices.reserve((int) ceil(numVertices * 0.3));

    // Heuristic for the maximum independent set problem
    while (!vertices.empty() && smallestVertexItr->degree != 0)
    {
        vertex = smallestVertexItr->index;
        independentVertices.push_back(vertex);
        vertices.erase(smallestVertexItr);
        removeNeighboors(vertex, vertices);
        smallestVertexItr = min_element(vertices.begin(), vertices.end(),
            [](Vertex &vertex0, Vertex &vertex1){
                return vertex0.degree < vertex1.degree;
            }
        );
    }
    getRemainingVertices(vertices, independentVertices);
    return independentVertices.size();
}

void resetGraph()
{
    numVertices = boardSize * boardSize;

    for (size_t i = 0; i < numVertices; i++)
        for (size_t j = 0; j < numVertices; j++)
            graph[i][j] = false;
}

void setVertexEdges(int vertexLine, int vertexColumn)
{
    int vertexIndex = vertexLine * boardSize + vertexColumn;
    // Create all edges with the positions on the right side
    int pawnColumn = findPawnColumn(vertexLine, vertexColumn + 1);

    for (size_t j = vertexColumn + 1, index = vertexIndex + 1;
        j < pawnColumn;
        j++, index++)
    {
        graph[vertexIndex][index] = graph[index][vertexIndex] = true;
    }

    // Create all edges with the positions below
    int pawnLine = findPawnLine(vertexLine + 1, vertexColumn);

    for (size_t i = vertexLine + 1, index = vertexIndex + boardSize;
        i < pawnLine;
        i++, index += boardSize)
    {
        graph[vertexIndex][index] = graph[index][vertexIndex] = true;
    }
}

void createAllEdgesForTheBoardGraph()
{
    for (size_t i = 0; i < boardSize; i++)
        for (size_t j = 0; j < boardSize; j++)
            if (board[i][j] == EMPTY)
                setVertexEdges(i, j);
}

int main()
{
    ios::sync_with_stdio(false);
        // auto start = chrono::steady_clock::now();
    string boardLine;
    cin >> boardSize;

    while (!cin.eof())
    {
        cin.ignore();

        for (size_t i = 0; i < boardSize; i++)
        {
            getline(cin, boardLine);
            for (size_t j = 0; j < boardSize; j++)
                board[i][j] = boardLine[j];
        }
        
        // auto start = chrono::steady_clock::now();
        resetGraph();
        createAllEdgesForTheBoardGraph();
        cout << getMaxNumTurrets_IndependentSet() << endl;
        // auto end = chrono::steady_clock::now();
        // cout << "Elapsed time in seconds : "
		// << chrono::duration_cast<chrono::seconds>(end - start).count()
		// << " sec" << endl;

        cin >> boardSize;
    }
        // auto end = chrono::steady_clock::now();
        // cout << "Elapsed time in seconds : "
		// << chrono::duration_cast<chrono::seconds>(end - start).count()
		// << " sec" << endl;
}
