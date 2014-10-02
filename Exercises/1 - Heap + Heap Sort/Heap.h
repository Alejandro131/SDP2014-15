#ifndef HEAP_H
#define HEAP_H

class Heap
{
    public:

        Heap();
        Heap(const Heap& other);
        Heap& operator = (const Heap& other);
        ~Heap();

        void insert(int element);
        bool pop(int &element);

        bool empty() const;

    private:

        void bubble(int index);
        void sink(int index);

        int leftChild(int index) const;
        int rightChild(int index) const;
        int parent(int index) const;

        bool exists(int index) const;

        void swapElements(int i, int j);

        void copyHeap(const Heap& other);
        void deleteHeap();

        void resize();

        int* container;
        int size;
        int capacity;

};

#endif // HEAP_H
