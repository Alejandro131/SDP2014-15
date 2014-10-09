#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>

using namespace std;

void mergeSort(int* arr, int size)
{
    if (size <= 2)
    {
        if (size == 2)
        {
            if (arr[0] > arr[1])
            {
                swap(arr[0], arr[1]);
            }
        }

        return;
    }

    mergeSort(arr, size / 2);
    mergeSort(arr + size / 2, (size + 1) / 2);

    merge(arr, size / 2, (size + 1) / 2);
}

void merge(int* arr, int sizeLeft, int size)
{
    vector<int> temp;

    int left = 0, right = 0;

    while (left < sizeLeft || right < size)
    {
        if (left < sizeLeft && right < size)
        {
            if (arr[left] > arr[right])
            {
                temp.push_back(arr[right]);
                right++;
            }
            else
            {
                temp.push_back(arr[left]);
                left++;
            }
        }
        else if (left < sizeLeft)
        {
            while (left < sizeLeft)
            {
                temp.push_back(arr[left]);
                left++;
            }
        }
        else
        {
            while (right < size)
            {
                temp.push_back(arr[right]);
                right++;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        arr[i] = temp[i];
    }
}

#endif