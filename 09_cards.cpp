#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include <string.h>

#define UNCOMPUTED INT32_MIN
#define MAX_NUM_CARDS 10000

int cards[MAX_NUM_CARDS];
long long results[MAX_NUM_CARDS][MAX_NUM_CARDS];

using namespace std;

void resetArrays(int numOfCards)
{
    memset(cards, 0, sizeof(int) * numOfCards);

    for (size_t i = 0; i < numOfCards; i++)
        for (size_t j = 0; j < numOfCards; j++)
            results[i][j] = UNCOMPUTED;
}

long long getGreatestNumOfPoints(int left, int right)
{
    if (results[left][right] != UNCOMPUTED)
        return results[left][right];

    if (left + 1 == right)
    {
        results[left][right] = max(cards[left], cards[right]);
        return results[left][right];
    }
    
    int leftValue = cards[left], rightValue = cards[right];
    long long leftRightPlay = getGreatestNumOfPoints(left + 1, right - 1);

    results[left][right] = max(
        min(
            leftValue + getGreatestNumOfPoints(left + 2, right),
            leftValue + leftRightPlay
        ),
        min(
            rightValue + getGreatestNumOfPoints(left, right - 2),
            rightValue + leftRightPlay
        )
    );

    return results[left][right];
}

int main()
{
    int numOfCards;
    cin >> numOfCards;

    while (!cin.eof())
    {
        resetArrays(numOfCards);

        for (size_t i = 0; i < numOfCards; i++) cin >> cards[i];

        cout << getGreatestNumOfPoints(0, numOfCards - 1) << endl;
        
        cin >> numOfCards;
    }
}
