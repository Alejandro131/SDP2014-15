#include "Heap.h"

Heap::Heap()
{
    //
}

Heap::Heap(const Heap& other)
{
    //
}

Heap& Heap::operator = (const Heap& other)
{
    //
}

Heap::~Heap()
{
    //
}

void Heap::copyHeap(const Heap& other)
{
    //
}

void Heap::deleteHeap()
{
    //
}

void Heap::resize()
{
    //
}

void Heap::insert(int element)
{
    if (size == capacity)
    {
        resize();
    }

    container[size] = element;
    size++;

    bubble(size - 1);
}

bool Heap::pop(int &element)
{
    if (empty())
    {
        return false;
    }

    element = container[0];
    swapElements(0, size - 1);
    size--;

    sink(0);

    return true;
}

void Heap::bubble(int index)
{
    while (index != 0)
    {
        int p = parent(index);

        if (container[p] > container[index])
        {
            swapElements(p, index);
            index = p;
        }
        else
        {
            // Pick one of the 3 possible solutions
            break;
            // index = 0;
            // return;
        }
    }
}

void Heap::sink(int index)
{
    while (index < size)
    {
        int l = leftChild(index);
        int r = rightChild(index);

        // Added this extra check in case both left and right children qualify for a swap
        if (exists(l) && exists(r) && container[index] > container[r] && container[index] > container[l])
        {
            if (container[r] > container[l])
            {
                swapElements(l, index);
                index = l;
            }
            else
            {
                swapElements(r, index);
                index = r;
            }
        } // end of extra check
        else if (exists(l) && container[index] > container[l])
        {
            swapElements(l, index);
            index = l;
        }
        else if (exists(r) && container[index] > container[r])
        {
            swapElements(r, index);
            index = r;
        }
        else
        {
            // Pick one of the 3 possible solutions
            break;
            // index = size;
            // return;
        }
    }
}

int Heap::leftChild(int index) const
{
    return index * 2 + 1;
}

int Heap::rightChild(int index) const
{
    return index * 2 + 2;
}

int Heap::parent(int index) const
{
    return (index - 1) / 2;
}

bool Heap::exists(int index) const
{
    return index < size;
}

void Heap::swapElements(int i, int j)
{
    int temp = container[i];
    container[i] = container[j];
    container[j] = temp;
}

bool Heap::empty() const
{
    return size == 0;
}
