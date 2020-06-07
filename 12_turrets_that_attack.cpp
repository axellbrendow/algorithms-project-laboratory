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
         _______                   _____                    _____                    _____                    _____                   _______         
        /::\    \                 /\    \                  /\    \                  /\    \                  /\    \                 /::\    \        
       /::::\    \               /::\____\                /::\    \                /::\____\                /::\    \               /::::\    \       
      /::::::\    \             /:::/    /               /::::\    \              /::::|   |               /::::\    \             /::::::\    \      
     /::::::::\    \           /:::/    /               /::::::\    \            /:::::|   |              /::::::\    \           /::::::::\    \     
    /:::/~~\:::\    \         /:::/    /               /:::/\:::\    \          /::::::|   |             /:::/\:::\    \         /:::/~~\:::\    \    
   /:::/    \:::\    \       /:::/    /               /:::/__\:::\    \        /:::/|::|   |            /:::/  \:::\    \       /:::/    \:::\    \   
  /:::/    / \:::\    \     /:::/    /               /::::\   \:::\    \      /:::/ |::|   |           /:::/    \:::\    \     /:::/    / \:::\    \  
 /:::/____/   \:::\____\   /:::/    /      _____    /::::::\   \:::\    \    /:::/  |::|   | _____    /:::/    / \:::\    \   /:::/____/   \:::\____\ 
|:::|    |     |:::|    | /:::/____/      /\    \  /:::/\:::\   \:::\    \  /:::/   |::|   |/\    \  /:::/    /   \:::\ ___\ |:::|    |     |:::|    |
|:::|____|     |:::|____||:::|    /      /::\____\/:::/  \:::\   \:::\____\/:: /    |::|   /::\____\/:::/____/     \:::|    ||:::|____|     |:::|    |
 \:::\   _\___/:::/    / |:::|____\     /:::/    /\::/    \:::\  /:::/    /\::/    /|::|  /:::/    /\:::\    \     /:::|____| \:::\    \   /:::/    / 
  \:::\ |::| /:::/    /   \:::\    \   /:::/    /  \/____/ \:::\/:::/    /  \/____/ |::| /:::/    /  \:::\    \   /:::/    /   \:::\    \ /:::/    /  
   \:::\|::|/:::/    /     \:::\    \ /:::/    /            \::::::/    /           |::|/:::/    /    \:::\    \ /:::/    /     \:::\    /:::/    /   
    \::::::::::/    /       \:::\    /:::/    /              \::::/    /            |::::::/    /      \:::\    /:::/    /       \:::\__/:::/    /    
     \::::::::/    /         \:::\__/:::/    /               /:::/    /             |:::::/    /        \:::\  /:::/    /         \::::::::/    /     
      \::::::/    /           \::::::::/    /               /:::/    /              |::::/    /          \:::\/:::/    /           \::::::/    /      
       \::::/____/             \::::::/    /               /:::/    /               /:::/    /            \::::::/    /             \::::/    /       
        |::|    |               \::::/    /               /:::/    /               /:::/    /              \::::/    /               \::/____/        
        |::|____|                \::/____/                \::/    /                \::/    /                \::/____/                 ~~              
         ~~                       ~~                       \/____/                  \/____/                  ~~                                       
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
      _____                   _______                   _____                    _____          
     /\    \                 /::\    \                 /\    \                  /\    \         
    /::\____\               /::::\    \               /::\    \                /::\    \        
   /:::/    /              /::::::\    \             /::::\    \              /::::\    \       
  /:::/    /              /::::::::\    \           /::::::\    \            /::::::\    \      
 /:::/    /              /:::/~~\:::\    \         /:::/\:::\    \          /:::/\:::\    \     
/:::/____/              /:::/    \:::\    \       /:::/  \:::\    \        /:::/__\:::\    \    
|::|    |              /:::/    / \:::\    \     /:::/    \:::\    \      /::::\   \:::\    \   
|::|    |     _____   /:::/____/   \:::\____\   /:::/    / \:::\    \    /::::::\   \:::\    \  
|::|    |    /\    \ |:::|    |     |:::|    | /:::/    /   \:::\    \  /:::/\:::\   \:::\    \ 
|::|    |   /::\____\|:::|____|     |:::|    |/:::/____/     \:::\____\/:::/__\:::\   \:::\____\
|::|    |  /:::/    / \:::\    \   /:::/    / \:::\    \      \::/    /\:::\   \:::\   \::/    /
|::|    | /:::/    /   \:::\    \ /:::/    /   \:::\    \      \/____/  \:::\   \:::\   \/____/ 
|::|____|/:::/    /     \:::\    /:::/    /     \:::\    \               \:::\   \:::\    \     
|:::::::::::/    /       \:::\__/:::/    /       \:::\    \               \:::\   \:::\____\    
\::::::::::/____/         \::::::::/    /         \:::\    \               \:::\   \::/    /    
 ~~~~~~~~~~                \::::::/    /           \:::\    \               \:::\   \/____/     
                            \::::/    /             \:::\    \               \:::\    \         
                             \::/____/               \:::\____\               \:::\____\        
                              ~~                      \::/    /                \::/    /        
                                                       \/____/                  \/____/         
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
          _____                    _____                _____                    _____                    _____                    _____                    _____          
         /\    \                  /\    \              /\    \                  /\    \                  /\    \                  /\    \                  /\    \         
        /::\    \                /::\    \            /::\    \                /::\    \                /::\____\                /::\    \                /::\    \        
       /::::\    \              /::::\    \           \:::\    \               \:::\    \              /:::/    /               /::::\    \              /::::\    \       
      /::::::\    \            /::::::\    \           \:::\    \               \:::\    \            /:::/    /               /::::::\    \            /::::::\    \      
     /:::/\:::\    \          /:::/\:::\    \           \:::\    \               \:::\    \          /:::/    /               /:::/\:::\    \          /:::/\:::\    \     
    /:::/__\:::\    \        /:::/__\:::\    \           \:::\    \               \:::\    \        /:::/____/               /:::/__\:::\    \        /:::/__\:::\    \    
   /::::\   \:::\    \       \:::\   \:::\    \          /::::\    \              /::::\    \       |::|    |               /::::\   \:::\    \      /::::\   \:::\    \   
  /::::::\   \:::\    \    ___\:::\   \:::\    \        /::::::\    \    ____    /::::::\    \      |::|    |     _____    /::::::\   \:::\    \    /::::::\   \:::\    \  
 /:::/\:::\   \:::\    \  /\   \:::\   \:::\    \      /:::/\:::\    \  /\   \  /:::/\:::\    \     |::|    |    /\    \  /:::/\:::\   \:::\    \  /:::/\:::\   \:::\____\ 
/:::/__\:::\   \:::\____\/::\   \:::\   \:::\____\    /:::/  \:::\____\/::\   \/:::/  \:::\____\    |::|    |   /::\____\/:::/__\:::\   \:::\____\/:::/  \:::\   \:::|    |
\:::\   \:::\   \::/    /\:::\   \:::\   \::/    /   /:::/    \::/    /\:::\  /:::/    \::/    /    |::|    |  /:::/    /\:::\   \:::\   \::/    /\::/   |::::\  /:::|____|
 \:::\   \:::\   \/____/  \:::\   \:::\   \/____/   /:::/    / \/____/  \:::\/:::/    / \/____/     |::|    | /:::/    /  \:::\   \:::\   \/____/  \/____|:::::\/:::/    / 
  \:::\   \:::\    \       \:::\   \:::\    \      /:::/    /            \::::::/    /              |::|____|/:::/    /    \:::\   \:::\    \            |:::::::::/    /  
   \:::\   \:::\____\       \:::\   \:::\____\    /:::/    /              \::::/____/               |:::::::::::/    /      \:::\   \:::\____\           |::|\::::/    /   
    \:::\   \::/    /        \:::\  /:::/    /    \::/    /                \:::\    \               \::::::::::/____/        \:::\   \::/    /           |::| \::/____/    
     \:::\   \/____/          \:::\/:::/    /      \/____/                  \:::\    \               ~~~~~~~~~~               \:::\   \/____/            |::|  ~|          
      \:::\    \               \::::::/    /                                 \:::\    \                                        \:::\    \                |::|   |          
       \:::\____\               \::::/    /                                   \:::\____\                                        \:::\____\               \::|   |          
        \::/    /                \::/    /                                     \::/    /                                         \::/    /                \:|   |          
         \/____/                  \/____/                                       \/____/                                           \/____/                  \|___|          
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
          _____                   _______                   _____                    _____                    _____                    _____                    _____                   _______         
         /\    \                 /::\    \                 /\    \                  /\    \                  /\    \                  /\    \                  /\    \                 /::\    \        
        /::\    \               /::::\    \               /::\    \                /::\____\                /::\    \                /::\____\                /::\    \               /::::\    \       
       /::::\    \             /::::::\    \             /::::\    \              /::::|   |                \:::\    \              /::::|   |               /::::\    \             /::::::\    \      
      /::::::\    \           /::::::::\    \           /::::::\    \            /:::::|   |                 \:::\    \            /:::::|   |              /::::::\    \           /::::::::\    \     
     /:::/\:::\    \         /:::/~~\:::\    \         /:::/\:::\    \          /::::::|   |                  \:::\    \          /::::::|   |             /:::/\:::\    \         /:::/~~\:::\    \    
    /:::/  \:::\    \       /:::/    \:::\    \       /:::/__\:::\    \        /:::/|::|   |                   \:::\    \        /:::/|::|   |            /:::/  \:::\    \       /:::/    \:::\    \   
   /:::/    \:::\    \     /:::/    / \:::\    \     /::::\   \:::\    \      /:::/ |::|   |                   /::::\    \      /:::/ |::|   |           /:::/    \:::\    \     /:::/    / \:::\    \  
  /:::/    / \:::\    \   /:::/____/   \:::\____\   /::::::\   \:::\    \    /:::/  |::|___|______    ____    /::::::\    \    /:::/  |::|   | _____    /:::/    / \:::\    \   /:::/____/   \:::\____\ 
 /:::/    /   \:::\ ___\ |:::|    |     |:::|    | /:::/\:::\   \:::\____\  /:::/   |::::::::\    \  /\   \  /:::/\:::\    \  /:::/   |::|   |/\    \  /:::/    /   \:::\ ___\ |:::|    |     |:::|    |
/:::/____/     \:::|    ||:::|____|     |:::|    |/:::/  \:::\   \:::|    |/:::/    |:::::::::\____\/::\   \/:::/  \:::\____\/:: /    |::|   /::\____\/:::/____/     \:::|    ||:::|____|     |:::|    |
\:::\    \     /:::|____| \:::\    \   /:::/    / \::/   |::::\  /:::|____|\::/    / ~~~~~/:::/    /\:::\  /:::/    \::/    /\::/    /|::|  /:::/    /\:::\    \     /:::|____| \:::\    \   /:::/    / 
 \:::\    \   /:::/    /   \:::\    \ /:::/    /   \/____|:::::\/:::/    /  \/____/      /:::/    /  \:::\/:::/    / \/____/  \/____/ |::| /:::/    /  \:::\    \   /:::/    /   \:::\    \ /:::/    /  
  \:::\    \ /:::/    /     \:::\    /:::/    /          |:::::::::/    /               /:::/    /    \::::::/    /                   |::|/:::/    /    \:::\    \ /:::/    /     \:::\    /:::/    /   
   \:::\    /:::/    /       \:::\__/:::/    /           |::|\::::/    /               /:::/    /      \::::/____/                    |::::::/    /      \:::\    /:::/    /       \:::\__/:::/    /    
    \:::\  /:::/    /         \::::::::/    /            |::| \::/____/               /:::/    /        \:::\    \                    |:::::/    /        \:::\  /:::/    /         \::::::::/    /     
     \:::\/:::/    /           \::::::/    /             |::|  ~|                    /:::/    /          \:::\    \                   |::::/    /          \:::\/:::/    /           \::::::/    /      
      \::::::/    /             \::::/    /              |::|   |                   /:::/    /            \:::\    \                  /:::/    /            \::::::/    /             \::::/    /       
       \::::/    /               \::/____/               \::|   |                  /:::/    /              \:::\____\                /:::/    /              \::::/    /               \::/____/        
        \::/____/                 ~~                      \:|   |                  \::/    /                \::/    /                \::/    /                \::/____/                 ~~              
         ~~                                                \|___|                   \/____/                  \/____/                  \/____/                  ~~                                       
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
          _____                    _____                            _____                   _______                   _____          
         /\    \                  /\    \                          /\    \                 /::\    \                 /\    \         
        /::\    \                /::\____\                        /::\____\               /::::\    \               /::\____\        
       /::::\    \              /:::/    /                       /:::/    /              /::::::\    \             /:::/    /        
      /::::::\    \            /:::/    /                       /:::/    /              /::::::::\    \           /:::/    /         
     /:::/\:::\    \          /:::/    /                       /:::/    /              /:::/~~\:::\    \         /:::/    /          
    /:::/__\:::\    \        /:::/    /                       /:::/____/              /:::/    \:::\    \       /:::/    /           
   /::::\   \:::\    \      /:::/    /                        |::|    |              /:::/    / \:::\    \     /:::/    /            
  /::::::\   \:::\    \    /:::/    /      _____              |::|    |     _____   /:::/____/   \:::\____\   /:::/    /      _____  
 /:::/\:::\   \:::\    \  /:::/____/      /\    \             |::|    |    /\    \ |:::|    |     |:::|    | /:::/____/      /\    \ 
/:::/__\:::\   \:::\____\|:::|    /      /::\____\            |::|    |   /::\____\|:::|____|     |:::|    ||:::|    /      /::\____\
\:::\   \:::\   \::/    /|:::|____\     /:::/    /            |::|    |  /:::/    / \:::\    \   /:::/    / |:::|____\     /:::/    /
 \:::\   \:::\   \/____/  \:::\    \   /:::/    /             |::|    | /:::/    /   \:::\    \ /:::/    /   \:::\    \   /:::/    / 
  \:::\   \:::\    \       \:::\    \ /:::/    /              |::|____|/:::/    /     \:::\    /:::/    /     \:::\    \ /:::/    /  
   \:::\   \:::\____\       \:::\    /:::/    /               |:::::::::::/    /       \:::\__/:::/    /       \:::\    /:::/    /   
    \:::\   \::/    /        \:::\__/:::/    /                \::::::::::/____/         \::::::::/    /         \:::\__/:::/    /    
     \:::\   \/____/          \::::::::/    /                  ~~~~~~~~~~                \::::::/    /           \::::::::/    /     
      \:::\    \               \::::::/    /                                              \::::/    /             \::::::/    /      
       \:::\____\               \::::/    /                                                \::/____/               \::::/    /       
        \::/    /                \::/____/                                                  ~~                      \::/____/        
         \/____/                  ~~                                                                                 ~~              
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
          _____                    _____                _____                    _____                    _____                            _____            _____          
         /\    \                  /\    \              /\    \                  /\    \                  /\    \                          /\    \          /\    \         
        /::\    \                /::\    \            /::\    \                /::\    \                /::\    \                        /::\____\        /::\    \        
       /::::\    \              /::::\    \           \:::\    \              /::::\    \              /::::\    \                      /:::/    /       /::::\    \       
      /::::::\    \            /::::::\    \           \:::\    \            /::::::\    \            /::::::\    \                    /:::/    /       /::::::\    \      
     /:::/\:::\    \          /:::/\:::\    \           \:::\    \          /:::/\:::\    \          /:::/\:::\    \                  /:::/    /       /:::/\:::\    \     
    /:::/__\:::\    \        /:::/__\:::\    \           \:::\    \        /:::/__\:::\    \        /:::/__\:::\    \                /:::/    /       /:::/__\:::\    \    
   /::::\   \:::\    \       \:::\   \:::\    \          /::::\    \      /::::\   \:::\    \      /::::\   \:::\    \              /:::/    /       /::::\   \:::\    \   
  /::::::\   \:::\    \    ___\:::\   \:::\    \        /::::::\    \    /::::::\   \:::\    \    /::::::\   \:::\    \            /:::/    /       /::::::\   \:::\    \  
 /:::/\:::\   \:::\    \  /\   \:::\   \:::\    \      /:::/\:::\    \  /:::/\:::\   \:::\    \  /:::/\:::\   \:::\____\          /:::/    /       /:::/\:::\   \:::\    \ 
/:::/__\:::\   \:::\____\/::\   \:::\   \:::\____\    /:::/  \:::\____\/:::/  \:::\   \:::\____\/:::/  \:::\   \:::|    |        /:::/____/       /:::/  \:::\   \:::\____\
\:::\   \:::\   \::/    /\:::\   \:::\   \::/    /   /:::/    \::/    /\::/    \:::\  /:::/    /\::/   |::::\  /:::|____|        \:::\    \       \::/    \:::\  /:::/    /
 \:::\   \:::\   \/____/  \:::\   \:::\   \/____/   /:::/    / \/____/  \/____/ \:::\/:::/    /  \/____|:::::\/:::/    /          \:::\    \       \/____/ \:::\/:::/    / 
  \:::\   \:::\    \       \:::\   \:::\    \      /:::/    /                    \::::::/    /         |:::::::::/    /            \:::\    \               \::::::/    /  
   \:::\   \:::\____\       \:::\   \:::\____\    /:::/    /                      \::::/    /          |::|\::::/    /              \:::\    \               \::::/    /   
    \:::\   \::/    /        \:::\  /:::/    /    \::/    /                       /:::/    /           |::| \::/____/                \:::\    \              /:::/    /    
     \:::\   \/____/          \:::\/:::/    /      \/____/                       /:::/    /            |::|  ~|                       \:::\    \            /:::/    /     
      \:::\    \               \::::::/    /                                    /:::/    /             |::|   |                        \:::\    \          /:::/    /      
       \:::\____\               \::::/    /                                    /:::/    /              \::|   |                         \:::\____\        /:::/    /       
        \::/    /                \::/    /                                     \::/    /                \:|   |                          \::/    /        \::/    /        
         \/____/                  \/____/                                       \/____/                  \|___|                           \/____/          \/____/         
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
*/

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
    // Check left
    // for (int i = column - 1; i >= 0; i--)
    // {
    //     if (board[line][i] == TURRET)
    //         return true;
    //     if (board[line][i] == PAWN)
    //         break;
    // }

    // Check right
    // for (int i = column + 1; i < boardSize; i++)
    // {
    //     if (board[line][i] == TURRET)
    //         return true;
    //     if (board[line][i] == PAWN)
    //         break;
    // }

    // Check up
    for (int i = line - 1; i >= 0; i--)
    {
        if (board[i][column] == TURRET)
            return true;
        if (board[i][column] == PAWN)
            break;
    }

    // Check down
    // for (int i = line + 1; i < boardSize; i++)
    // {
    //     if (board[i][column] == TURRET)
    //         return true;
    //     if (board[i][column] == PAWN)
    //         break;
    // }

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
int num = 0;
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
        // cout << getMaxNumTurrets_Backtracking() << endl;
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
