#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int getMaxSumForElement(int x, int y, vector<vector<int>>& matrix, int matrixSize)
{
    int maxSum = INT_MIN;

    return maxSum;
}

int getMaximalSubrectangleSum(vector<vector<int>>& matrix, int matrixSize)
{
    int maxSum = INT_MIN;

    for (size_t i = 0; i < matrixSize; i++)
    {
        for (size_t j = 0; j < matrixSize; j++)
        {
            maxSum = getMaxSumForElement(i, j, matrix, matrixSize);
        }
    }

    return maxSum;
}

int main()
{
    int matrixSize;
    cin >> matrixSize;

    vector<vector<int>> matrix(matrixSize);

    for (size_t i = 0; i < matrixSize; i++)
    {
        matrix[i] = vector<int>(matrixSize);

        for (size_t j = 0; j < matrixSize; j++)
        {
            cin >> matrix[i][j];
        }

        cout << endl;
    }

    cout << getMaximalSubrectangleSum(matrix, matrixSize);
}
