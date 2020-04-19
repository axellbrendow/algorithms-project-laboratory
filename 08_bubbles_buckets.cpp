#include <iostream>

using namespace std;

int numOfPlays = 0;

void merge(int array[], int size)
{
    int mid = size / 2;
    int i = 0, j = mid, k = 0;
    int aux[size];

    while (i < mid && j < size)
    {
        if (array[i] <= array[j]) aux[k] = array[i++];
        else
        {
            numOfPlays += j - k;
            aux[k] = array[j++];
        }
        k++;
    }

    if (i == mid)
        while (j < size)
        {
            numOfPlays += j - k;
            aux[k++] = array[j++];
        }
    else
        while (i < mid) aux[k++] = array[i++];

    for (i = 0; i < size; i++) array[i] = aux[i];
}

void mergeSort(int array[], int size)
{
    if (size > 1)
    {
        int mid = size / 2;
        mergeSort(array, mid);
        mergeSort(array + mid, size - mid);
        merge(array, size);
    }
}

int main()
{
    int sequenceSize;
    cin >> sequenceSize;

    while (sequenceSize > 0)
    {
        int sequence[sequenceSize];

        for (size_t i = 0; i < sequenceSize; i++) cin >> sequence[i];
        
        numOfPlays = 0;
        mergeSort(sequence, sequenceSize);
        cout << (numOfPlays % 2 == 0 ? "Carlos" : "Marcelo") << endl;
        cin >> sequenceSize;
    }

    return 0;
}
