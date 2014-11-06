#include "Hash.h"

Hash::Hash(int bucketCount = 15)
{
    this->bucketCount = bucketCount;
    for (int i = 0; i < bucketCount; i++)
    {
        vector<HashEntry> v;
        buckets.push_back(v);
    }
}

bool Hash::get(int key, int& value) const
{
    int hash = hashKey(key);
    bool found = false;

    for (int i = 0; i < buckets[hash].size(); i++)
    {
        if (buckets[hash][i].key == key)
        {
            value = buckets[hash][i].value;
            found = true;
            break;
        }
    }

    return found;
}

void Hash::put(int key, int value)
{
    int hash = hashKey(key);

    HashEntry temp;
    temp.key = key;
    temp.value = value;

    buckets[hash].push_back(temp);
}

int Hash::hashKey(int key) const
{
    // could be a prime number multiplication sum by digits of the key
    return key % bucketCount;
}
