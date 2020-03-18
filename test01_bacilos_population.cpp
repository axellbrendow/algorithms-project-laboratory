#include <iostream>

using namespace std;

int fibonnaci(unsigned long long n)
{
    int lastElem = 1;
    int currElem = 1;
    int aux;
    // printf("%d %d", lastElem, currElem);
    for (unsigned long long i = 2; i < n; i++)
    {
        aux = lastElem;
        lastElem = currElem;
        currElem += aux;
        currElem = currElem % 1000;
        // printf(" %d", currElem);
    }
    // puts("");
    return currElem;
}

int main()
{
    int numTests;
    unsigned long long timeRange;
    cin >> numTests;

    for (size_t i = 0; i < numTests; i++)
    {
        cin >> timeRange;
        cout << timeRange << endl;
        timeRange = timeRange % 1500;
        printf("%03d\n", timeRange == 0 ? 0 : fibonnaci(timeRange));
    }
}
