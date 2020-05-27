#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main()
{
    /** Matrices dimensions (ignore index 0), in this case,
     * A[15][20], B[20][13], C[13][5], D[5][8], E[8][50], F[50][6] */
    int dimensions[] = {0, 15, 20, 13, 5, 8, 50, 6};
    int numR = sizeof(dimensions) / sizeof(int);
    int numMatrices = numR - 2;
    int cost[numMatrices + 1][numMatrices + 1];
    int best[numMatrices + 1][numMatrices + 1];

    // Init matrices
    for (size_t i = 0; i <= numMatrices; i++)
        for (size_t j = 0; j <= numMatrices; j++)
            best[i][j] = -1;

    for (size_t i = 0; i <= numMatrices; i++)
        for (size_t j = 0; j <= numMatrices; j++)
            cost[i][j] = INT32_MAX;

    for (size_t i = 1; i <= numMatrices; i++)
        cost[i][i] = 0;

    // Run algorithm
    for (int offset = 1; offset < numMatrices; offset++)
        for (int leftMatrix = 1; leftMatrix <= numMatrices - offset; leftMatrix++)
            for (int parenPos = leftMatrix + 1; parenPos <= leftMatrix + offset;
                 parenPos++)
            {
                int t = cost[leftMatrix][parenPos - 1] +
                        cost[parenPos][leftMatrix + offset] +
                        dimensions[leftMatrix] * dimensions[parenPos] *
                            dimensions[leftMatrix + offset + 1];

                if (t < cost[leftMatrix][leftMatrix + offset])
                {
                    cost[leftMatrix][leftMatrix + offset] = t;
                    best[leftMatrix][leftMatrix + offset] = parenPos;
                }
            }

    // Print results
    printf("cost\n");
    for (size_t i = 1; i <= numMatrices; i++)
    {
        for (size_t j = 1; j <= numMatrices; j++)
        {
            printf("%10d ", cost[i][j]);
        }
        printf("\n");
    }

    printf("\nbest\n");
    for (size_t i = 1; i <= numMatrices; i++)
    {
        for (size_t j = 1; j <= numMatrices; j++)
        {
            printf("%3d ", best[i][j]);
        }
        printf("\n");
    }

    return 0;
}
