#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <vector>

using namespace std;

void radixSort(int* arr, int size)
{
    int largest = arr[0];

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > largest)
        {
            largest = arr[i];
        }
    }

    int numberOfPasses = 0;

    while (largest > 0)
    {
        numberOfPasses++;
        largest /= 10;
    }

    int digit;

    for (int t = 0, divisor = 1; t < numberOfPasses; t++, divisor *= 10)
    {
        vector<int> bucket[10];

        for (int i = 0; i < size; i++)
        {
            digit = (arr[i] / divisor) % 10;
            bucket[digit].push_back(arr[i]);
        }

        int k = 0;

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < bucket[i].size(); j++)
            {
                   arr[k++] = bucket[i][j];
            }
        }
    }
}

#endif