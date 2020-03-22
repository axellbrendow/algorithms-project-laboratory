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

int digitToInt(char digit) { return digit - '0'; }

unsigned long long takeStrModulo(unsigned long long modulo, string numericStr)
{
    int length = numericStr.length();
    unsigned long long result = 0;

    for (int i = 0; i < length; i++)
    {
        result = (result * 10 + digitToInt(numericStr[i])) % modulo;
    }
    
    return result;
}

int main()
{
    int numTests;
    string timeRange;
    unsigned long long timeRangeAsNum;
    cin >> numTests;

    for (size_t i = 0; i < numTests; i++)
    {
        cin >> timeRange;
        timeRangeAsNum = takeStrModulo(1500, timeRange);
        printf("%03d\n", timeRangeAsNum == 0 ? 0 : fibonnaci(timeRangeAsNum));
    }
}
