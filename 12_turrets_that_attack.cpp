#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
#include <algorithm>

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

// void discoverPositionForNextTurret(
//     int startingLine, int startingColumn, int &line, int &column)
// {
//     for (size_t j = startingColumn; j < boardSize; j++)
//         if (board[startingLine][j] == EMPTY)
//         {
//             line = startingLine;
//             column = j;
//             return;
//         }

//     for (size_t i = startingLine + 1; i < boardSize; i++)
//         for (size_t j = 0; j < boardSize; j++)
//             if (board[i][j] == EMPTY)
//             {
//                 line = i;
//                 column = j;
//                 return;
//             }
// }

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

// bool turretCanBeAttacked(int line, int column)
// {
//     // Check left
//     // for (int i = column - 1; i >= 0; i--)
//     // {
//     //     if (board[line][i] == TURRET)
//     //         return true;
//     //     if (board[line][i] == PAWN)
//     //         break;
//     // }

//     // Check right
//     // for (int i = column + 1; i < boardSize; i++)
//     // {
//     //     if (board[line][i] == TURRET)
//     //         return true;
//     //     if (board[line][i] == PAWN)
//     //         break;
//     // }

//     // Check up
//     for (int i = line - 1; i >= 0; i--)
//     {
//         if (board[i][column] == TURRET)
//             return true;
//         if (board[i][column] == PAWN)
//             break;
//     }

//     // Check down
//     // for (int i = line + 1; i < boardSize; i++)
//     // {
//     //     if (board[i][column] == TURRET)
//     //         return true;
//     //     if (board[i][column] == PAWN)
//     //         break;
//     // }

//     return false;
// }

void printBoard(int numTurrets)
{
    cout << "BOARD " << boardSize << "x" << boardSize
         << " (numTurrets = " << numTurrets << ")" << endl;
    for (size_t i = 0; i < boardSize; i++)
    {
        for (size_t j = 0; j < boardSize; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "==================" << endl
         << endl;
}

// void changeBoard(int line, int column, char value, int numTurrets)
// {
//     board[line][column] = value;
//     printBoard(numTurrets);
//     system("sleep 0.5; clear");
// }

// void placeTurret(int line, int column, int numTurrets, int &maxNumTurrets)
// {
//     numTurrets++;
//     int pawnColumn = findPawnColumn(line, column + 1);
//     int nextTurretLine, nextTurretColumn;

//     for (size_t i = column; i < pawnColumn; i++)
//     {
//         if (turretCanBeAttacked(line, i))
//             continue;

//         int startLine = line, startColumn = pawnColumn + 1;
//         // changeBoard(line, i, TURRET, numTurrets);
//         board[line][i] = TURRET;
//         do
//         {
//             nextTurretLine = nextTurretColumn = -1;
//             discoverPositionForNextTurret(
//                 startLine, startColumn, nextTurretLine, nextTurretColumn);

//             if (nextTurretLine == -1 || nextTurretColumn == -1)
//             {
//                 // printBoard(numTurrets);
//                 if (numTurrets > maxNumTurrets)
//                     maxNumTurrets = numTurrets;
//                 // changeBoard(line, i, EMPTY, numTurrets);
//                 board[line][i] = EMPTY;
//                 return;
//             }

//             startLine = nextTurretLine;
//             startColumn = nextTurretColumn + 1;

//         } while (turretCanBeAttacked(nextTurretLine, nextTurretColumn));

//         placeTurret(nextTurretLine, nextTurretColumn, numTurrets, maxNumTurrets);
//         board[line][i] = EMPTY;
//     }
// }

// int getMaxNumTurrets()
// {
//     int line = -1, column = -1;
//     discoverPositionForNextTurret(0, 0, line, column);

//     if (line == -1 || column == -1)
//         return 0;

//     int maxNumTurrets = 0;
//     placeTurret(line, column, 0, maxNumTurrets);
//     return maxNumTurrets;
// }

int getVertexWithSmallestDegree(vector<int> &vertices)
{
    int bestVertex = -1, degree, smallestDegree = INT32_MAX;

    for (auto &&vertex : vertices)
    {
        degree = 0;

        for (size_t i = 0; i < numVertices; i++)
            if (graph[vertex][i]) degree++;

        if (degree != 0 && degree < smallestDegree)
        {
            smallestDegree = degree;
            bestVertex = vertex;
        }
    }
    
    return bestVertex;
}

void removeNeighboors(int vertex, vector<int> &vertices)
{
    for (size_t i = 0; i < numVertices; i++)
        if (graph[vertex][i]) // Check if the vertex `i` is a neighboor of `vertex`
        {
            for (size_t j = 0; j < numVertices; j++) // Remove all edges from `i`
                graph[i][j] = graph[j][i] = false;
            
            vertices.erase(find(vertices.begin(), vertices.end(), i));
        }
}

int getMaxNumTurrets()
{
    // Print board and graph
    // printBoard(0);

    // cout << "GRAPH" << endl;
    // for (size_t i = 0; i < numVertices; i++)
    // {
    //     for (size_t j = 0; j < numVertices; j++) cout << graph[i][j] << " ";
    //     cout << endl;
    // }
    // cout << endl;

    vector<int> vertices;
    // Get all vertices that represent an empty position in the board
    for (size_t i = 0; i < numVertices; i++)
    {
        int line = i / boardSize;
        int column = i % boardSize;
        if (board[line][column] == EMPTY) vertices.push_back(i);
    }
    
    int vertex;
    vector<int> independentVertices; // To store the maximum independent set of vertices.
    independentVertices.reserve((int) ceil(numVertices * 0.3));

    while (!vertices.empty()) // Heuristic for the maximum independent set problem
    {
        vertex = getVertexWithSmallestDegree(vertices);
        if (vertex != -1)
        {
            independentVertices.push_back(vertex);
            vertices.erase(find(vertices.begin(), vertices.end(), vertex));
            removeNeighboors(vertex, vertices);
        }
    }

    // If there are remaining vertices in the `vertices` vector, these vertices
    // belong to the maximum independent set
    for (auto &&vertex : vertices)
    {
        independentVertices.push_back(vertex);
        vertices.erase(find(vertices.begin(), vertices.end(), vertex));
    }

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

        resetGraph();
        createAllEdgesForTheBoardGraph();
        cout << getMaxNumTurrets() << endl;
        cin >> boardSize;
    }
}
