#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

void insertionSort(int* arr, int size)
{
    int elem;

    for (int i = 1; i < size; i++)
    {
        elem = arr[i];

        for (int j = i - 1; j >= 0; j--)
        {
            if (elem < arr[j])
            {
                swap(arr[j], arr[j + 1]);
            }
            else
            {
                break;
            }
        }
    }
}

#endif