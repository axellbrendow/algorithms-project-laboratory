#include <iostream>
#include <string.h>

using namespace std;

void printCosts(int cost[], int best[], int object, int knapSackSize)
{
    // print header
    printf("object array  ");
    for (size_t i = 0; i < knapSackSize; i++)
    {
        printf("%2lu ", i);
    }
    cout << endl;
    
    // print cost array
    printf("%6d cost[]", object);
    for (size_t i = 0; i < knapSackSize; i++)
    {
        printf(" %2d", cost[i]);
    }
    cout << endl;
    
    // print best array
    printf("%6d best[]", object);
    for (size_t i = 0; i < knapSackSize; i++)
    {
        printf(" %2c", (char)(best[i] + 'A'));
    }
    cout << endl;
}

int knapSack(int knapSackSize, int size[], int val[], int n, int cost[], int best[])
{
    int valueAddingNewObject, objectValue, objectSize;

    for (size_t object = 0; object < n; object++)
    {
        objectSize = size[object];
        objectValue = val[object];

        for (size_t capacity = 0; capacity < knapSackSize; capacity++)
        {
            if (capacity >= objectSize)
            {
                //                          capacity - objectSize  represents
                // removing from the knap                          sack some objects
                // that together have                              a size of
                // "objectSize"
                //                     cost[capacity - objectSize] represents the
                // value we get with                               that capacity
                valueAddingNewObject = cost[capacity - objectSize] + objectValue;

                // Check if the amount of value we get with current capacity is
                // smaller than what we could get adding the current object
                if (cost[capacity] < valueAddingNewObject)
                {
                    cost[capacity] = valueAddingNewObject;
                    // At that capacity, the best object is "object"
                    best[capacity] = object;
                }
            }
        }

        printCosts(cost, best, object, knapSackSize);
        cout << endl;
    }
}

int main()
{
    int size[] = {1, 4, 5, 6};
    int val[] = {1, 5, 6, 8};
    int knapSackSize = 15;
    int n = sizeof(val) / sizeof(val[0]);
    int cost[knapSackSize];
    int best[knapSackSize];
    memset(cost, 0, sizeof(cost));
    memset(best, 0, sizeof(best));
    knapSack(knapSackSize, size, val, n, cost, best);
    cout << cost[knapSackSize - 1] << endl;
    return 0;
}
