#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int getMaxVectorSum(vector<int>& vector)
{
    int size = vector.size();
    int sum = 0, maxSum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += vector[i];

        if (sum < 0) sum = 0;
        else if (sum > maxSum) maxSum = sum;
    }
    
    return maxSum;
}

int getMaximalSubrectangleSum(vector<vector<int>>& matrix, int matrixSize)
{
    vector<int> columnSum(matrixSize, 0);
    int maxSum = INT_MIN;
    int sum;

    for (size_t left = 0; left < matrixSize; left++)
    {
        for (size_t right = left; right < matrixSize; right++)
        {
            for (size_t line = 0; line < matrixSize; line++)
            {
                columnSum[line] += matrix[line][right];
            }
            
            sum = getMaxVectorSum(columnSum);
            if (sum > maxSum) maxSum = sum;
        }

        fill(columnSum.begin(), columnSum.end(), 0);
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
