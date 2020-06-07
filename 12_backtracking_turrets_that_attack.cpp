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

void discoverPositionForNextTurret(
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

int findPawnLine(int startingLine, int column)
{
    int pawnLine = startingLine;
    while (pawnLine < boardSize && board[pawnLine][column] != PAWN)
        pawnLine++;
    return pawnLine;
}

bool turretCanBeAttacked(int line, int column)
{
    for (int i = line - 1; i >= 0; i--) // Check up
    {
        if (board[i][column] == TURRET)
            return true;
        if (board[i][column] == PAWN)
            break;
    }

    return false;
}

void printBoard(int numTurrets)
{
    cout << "BOARD " << boardSize << "x" << boardSize
         << " (numTurrets = " << numTurrets << ")" << endl;

    for (size_t i = 0; i < boardSize; i++)
    {
        for (size_t j = 0; j < boardSize; j++) cout << board[i][j] << " ";
        cout << endl;
    }
    cout << "==================" << endl << endl;
}

void changeBoard(int line, int column, char value, int numTurrets)
{
    board[line][column] = value;
    printBoard(numTurrets);
    system("sleep 0.3; clear");
}
// int num = 0;
void placeTurret(int line, int column, int numTurrets, int &maxNumTurrets)
{
    // cout << "num: " << num++ << ", line" << line << ", column: " << column << endl;
    numTurrets++;
    int pawnColumn = findPawnColumn(line, column + 1);
    int nextTurretLine, nextTurretColumn;

    for (size_t i = column; i < pawnColumn; i++)
    {
        if (turretCanBeAttacked(line, i))
            continue;

        int startLine = line, startColumn = pawnColumn + 1;
        // changeBoard(line, i, TURRET, numTurrets);
        board[line][i] = TURRET;
        do
        {
            nextTurretLine = nextTurretColumn = -1;
            discoverPositionForNextTurret(
                startLine, startColumn, nextTurretLine, nextTurretColumn);

            if (nextTurretLine == -1 || nextTurretColumn == -1)
            {
                // printBoard(numTurrets);
                if (numTurrets > maxNumTurrets)
                    maxNumTurrets = numTurrets;
                // changeBoard(line, i, EMPTY, numTurrets);
                board[line][i] = EMPTY;
                return;
            }

            startLine = nextTurretLine;
            startColumn = nextTurretColumn + 1;

        } while (turretCanBeAttacked(nextTurretLine, nextTurretColumn));

        placeTurret(nextTurretLine, nextTurretColumn, numTurrets, maxNumTurrets);
        board[line][i] = EMPTY;
    }
}

int getMaxNumTurrets_Backtracking()
{
    int line = -1, column = -1;
    discoverPositionForNextTurret(0, 0, line, column);

    if (line == -1 || column == -1)
        return 0;

    int maxNumTurrets = 0;
    placeTurret(line, column, 0, maxNumTurrets);
    return maxNumTurrets;
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
        cout << getMaxNumTurrets_Backtracking() << endl;
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
