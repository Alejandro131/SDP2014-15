#ifndef SHELL_SORT_H
#define SHELL_SORT_H

void shellSort(int* arr, int size)
{
    int elem;
    int gaps[3] = {3, 2, 1};

    for (int t = 0; t < 3; t++)
    {
        int gap = gaps[t];

        for (int i = gap; i < size; i++)
        {
            elem = arr[i];

            for (int j = i - gap; j >= 0; j -= gap)
            {
                if (elem < arr[j])
                {
                    swap(arr[j], arr[j + gap]);
                }
                else
                {
                    break;
                }
            }
        }
    }
}

#endif