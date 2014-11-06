#ifndef HASH_H
#define HASH_H

#include <vector>

using namespace std;

struct HashEntry
{
    int key;
    int value;
};

class Hash
{
    public:

        Hash(int bucketCount = 15);

        bool get(int key, int& value) const;
        void put(int key, int value);

    private:

        int hashKey(int key) const;
        
        vector< vector< HashEntry > > buckets;
        int bucketCount;
};

#endif