#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// l = line, c = column
int sumMatrix(vector<vector<int>>& matrix, int l0, int c0, int l1, int c1)
{
    int sum = 0;

    for (size_t i = l0; i <= l1; i++)
        for (size_t j = c0; j <= c1; j++)
            sum += matrix[i][j];
    
    return sum;
}

// l = line, c = column
int getMaxSumForElement(int l, int c, vector<vector<int>>& matrix, int matrixSize)
{
    int maxSum = INT_MIN;
    int sum;

    for (size_t i = l; i < matrixSize; i++)
        for (size_t j = c; j < matrixSize; j++)
        {
            sum = sumMatrix(matrix, l, c, i, j);
            maxSum = sum > maxSum ? sum : maxSum;
        }

    return maxSum;
}

int getMaximalSubrectangleSum(vector<vector<int>>& matrix, int matrixSize)
{
    int maxSum = INT_MIN;
    int sum;

    for (size_t i = 0; i < matrixSize; i++)
        for (size_t j = 0; j < matrixSize; j++)
        {
            sum = getMaxSumForElement(i, j, matrix, matrixSize);
            maxSum = sum > maxSum ? sum : maxSum;
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

        for (size_t j = 0; j < matrixSize; j++) cin >> matrix[i][j];
    }

    cout << getMaximalSubrectangleSum(matrix, matrixSize) << endl;
}
