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

/*
REFERENCES:

https://www.urionlinejudge.com.br/judge/en/problems/view/1490
https://graphonline.ru/en/create_graph_by_matrix
https://csacademy.com/app/graph_editor/
https://www.geeksforgeeks.org/maximum-bipartite-matching/
https://www.youtube.com/watch?v=x2BdRml5lmc
http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/NetFlow/max-flow-alg.html
https://github.com/Walissonpj/Issues-Resolved---URI/blob/master/Graphs/1490.cpp
*/

#define MAX_BOARD_SIZE 100
#define MAX_NUM_VERTICES (MAX_BOARD_SIZE * MAX_BOARD_SIZE)
#define TURRET 'T'
#define PAWN 'X'
#define EMPTY '.'

bool graph[MAX_NUM_VERTICES][MAX_NUM_VERTICES];
int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int boardWithLineIDs[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int boardWithColumnIDs[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int boardSize;
int numLinePieces;
int numColumnPieces;

void discoverNextLinePieceStart(
    int startingLine, int startingColumn, int &line, int &column)
{
    for (size_t j = startingColumn; j < boardSize; j++)
        if (board[startingLine][j] == EMPTY)
        {
            line = startingLine;
            column = j;
            return;
        }

    for (size_t i = startingLine + 1; i < boardSize; i++)
        for (size_t j = 0; j < boardSize; j++)
            if (board[i][j] == EMPTY)
            {
                line = i;
                column = j;
                return;
            }
}

int findPawnColumn(int line, int startingColumn)
{
    int pawnColumn = startingColumn;
    while (pawnColumn < boardSize && board[line][pawnColumn] != PAWN)
        pawnColumn++;
    return pawnColumn;
}

void discoverNextColumnPieceStart(
    int startingLine, int startingColumn, int &line, int &column)
{
    for (size_t i = startingLine; i < boardSize; i++)
        if (board[i][startingColumn] == EMPTY)
        {
            line = i;
            column = startingColumn;
            return;
        }

    for (size_t j = startingColumn + 1; j < boardSize; j++)
        for (size_t i = 0; i < boardSize; i++)
            if (board[i][j] == EMPTY)
            {
                line = i;
                column = j;
                return;
            }
}

int findPawnLine(int startingLine, int column)
{
    int pawnLine = startingLine;
    while (pawnLine < boardSize && board[pawnLine][column] != PAWN)
        pawnLine++;
    return pawnLine;
}

void printGraph()
{
    cout << "GRAPH" << endl;
    for (size_t i = 0; i < numLinePieces; i++)
    {
        for (size_t j = 0; j < numColumnPieces; j++) cout << graph[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

int discoverLinePieces()
{
    int lineID = 0, startLine = 0, startColumn = 0, endColumn;
    while (true)
    {
        int outputLine = -1, outputColumn = -1;
        discoverNextLinePieceStart(startLine, startColumn, outputLine, outputColumn);
        if (outputLine == -1 || outputColumn == -1) return lineID;

        endColumn = findPawnColumn(outputLine, outputColumn);

        // Put same line ID for all columns of this line piece
        for (size_t i = outputColumn; i < endColumn; i++)
            boardWithLineIDs[outputLine][i] = lineID;
        
        lineID++;
        startLine = outputLine;
        startColumn = endColumn + 1;
    }
}

int discoverColumnPieces()
{
    int columnID = 0, startColumn = 0, startLine = 0, endLine;
    while (true)
    {
        int outputColumn = -1, outputLine = -1;
        discoverNextColumnPieceStart(startLine, startColumn, outputLine, outputColumn);
        if (outputColumn == -1 || outputLine == -1) return columnID;

        endLine = findPawnLine(outputLine, outputColumn);

        // Put same column ID for all columns of this column piece
        for (size_t i = outputLine; i < endLine; i++)
        {
            boardWithColumnIDs[i][outputColumn] = columnID;
            graph[columnID][boardWithLineIDs[i][outputColumn]] = true;
        }
        
        columnID++;
        startColumn = outputColumn;
        startLine = endLine + 1;
    }
}

// returns true if columnPiece has a corresponding linePiece to match
bool DFS(int columnPiece, bool visited[], int columnPieces[])
{
    for (int linePiece = 0; linePiece < numLinePieces; linePiece++)
    {
        // If columnPiece has an edge with linePiece and linePiece is not visited
        if (graph[columnPiece][linePiece] && !visited[linePiece])
        {
            visited[linePiece] = true;

            if (columnPieces[linePiece] == -1
                || DFS(columnPieces[linePiece], visited, columnPieces))
            {
                columnPieces[linePiece] = columnPiece;
                return true;
            }
        }
    }
    return false;
}

int getMaxNumTurrets_MaximumMatching()
{
    // columnPieces[i] means column piece associated with line piece i
    // -1 indicates that line piece i has no column piece associated
    int columnPieces[numLinePieces];

    // Initially all line pieces are available
    memset(columnPieces, -1, sizeof(columnPieces));

    // Number of line pieces used with a column piece
    int result = 0;
    for (int columnPiece = 0; columnPiece < numColumnPieces; columnPiece++)
    {
        // Mark all line pieces as not visited
        bool visited[numLinePieces];
        memset(visited, 0, sizeof(visited));

        // Check if column piece can get a line piece that wasn't used.
        // If yes, we can place a turret (or rook).
        if (DFS(columnPiece, visited, columnPieces)) result++;
    }
    return result;
}

void printBoard(int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE])
{
    for (size_t i = 0; i < boardSize; i++)
    {
        for (size_t j = 0; j < boardSize; j++) cout << board[i][j] << " ";
        cout << endl;
    }
    cout << "==================" << endl << endl;
}

int getMaxNumTurrets_MaximumMatching_Start()
{
    memset(graph, false, sizeof(graph));
    // for (size_t i = 0; i < boardSize; i++)
    //     for (size_t j = 0; j < boardSize; j++)
    //         boardWithLineIDs[i][j] = boardWithColumnIDs[i][j] = board[i][j];
    
    numLinePieces = discoverLinePieces();
    numColumnPieces = discoverColumnPieces();
    // printBoard(board);
    // printBoard(boardWithLineIDs);
    // printBoard(boardWithColumnIDs);
    // printGraph(numLinePieces, numColumnPieces);
    // cout << "<<<<<<<<<<<<<<<<<<<<<<<<<end>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    // createBipartiteFlowGraph();
    return getMaxNumTurrets_MaximumMatching();
}

int main()
{
    ios::sync_with_stdio(false);
        auto start = chrono::steady_clock::now();
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
        // resetGraph();
        cout << getMaxNumTurrets_MaximumMatching_Start() << endl;
        // auto end = chrono::steady_clock::now();
        // cout << "Elapsed time in seconds : "
		// << chrono::duration_cast<chrono::seconds>(end - start).count()
		// << " sec" << endl;

        cin >> boardSize;
    }
        auto end = chrono::steady_clock::now();
        cout << "Elapsed time in seconds : "
		<< chrono::duration_cast<chrono::seconds>(end - start).count()
		<< " sec" << endl;
}
