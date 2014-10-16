#ifndef QUICK_SORT_H
#define QUICK_SORT_H

void quickSort(int* arr, int size)
{
    if (size <= 1)
        return;

    if (size == 2)
    {
        if (arr[0] > arr[1])
        {
            swap(arr[0], arr[1]);
        }
        return;
    }

    int pivotIndex = rand() % size;
    int pivot = arr[pivotIndex];

    if (pivotIndex != size - 1)
	{
        swap(arr[pivotIndex], arr[size - 1]);
	}

    int left = 0;
    int right = size - 2;

    while (left < right)
    {
        for (int i = left; i <= size - 2; i++)
        {
            if (arr[i] > pivot)
            {
                left = i;
                break;
            }
            else
            {
                if (i == size - 2)
                {
                    left = i;
                }
            }
        }

        for (int j = right; j >= 0; j--)
        {
            if (arr[j] <= pivot)
            {
                right = j;
                break;
            }
            else
            {
                if (j == 0)
                {
                    right = j;
                }
            }
        }

        if (left < right)
        {
            swap(arr[left], arr[right]);
        }
    }

    if (left != size - 1)
    {
        swap(arr[left], arr[size - 1]);
    }

    quickSort(arr, left);
    quickSort(arr + left, size - left);
}

#endif