#include <iostream>
using namespace std;

struct HashItem
{
    int key;
    string value;
    short status;

    HashItem(int status = 0) : key(0), value(""), status(status) {}
};

class HashMap
{
private:
    HashItem *hashArray;
    int capacity;
    int currentElements;
    int getNextCandidateIndex(int key, int i)
    {
        return (key + (i * i)) % capacity;
    }

public:
    HashMap()
    {
        capacity = 10;
        currentElements = 0;
        hashArray = new HashItem[capacity];
    }

    HashMap(int const capacity)
    {
        if (capacity > 1)
        {
            currentElements = 0;
            this->capacity = capacity;
            hashArray = new HashItem[capacity];

            return;
        }

        cout << "Error (capcity should greater than 1)!";
        exit(0);
    }

    void insert(int const key, string const value)
    {
        int index = key % capacity;

        int i = 1;
        while (hashArray[index].status == 2)
        {
            index = getNextCandidateIndex(key, i);
            i++;
        }

        hashArray[index].key = key;
        hashArray[index].value = value;
        hashArray[index].status = 2;

        currentElements++;

        // Check load factor and double the capacity if necessary
        if (static_cast<double>(currentElements) / capacity >= 0.75)
        {
            doubleCapacity();
        }
    }

    bool deleteKey(int const key)
    {
        int index = key % capacity;
        int i = 1;

        while (hashArray[index].status != 0)
        {
            if (hashArray[index].key == key && hashArray[index].status == 2)
            {
                hashArray[index].status = 1; // Mark as deleted
                currentElements--;
                return true;
            }

            index = getNextCandidateIndex(key, i);
            i++;
        }

        return false; // Key not found
    }

    string get(int const key)
    {
        int index = key % capacity;
        int i = 1;

        while (hashArray[index].status != 0)
        {
            if (hashArray[index].key == key && hashArray[index].status == 2)
            {
                return hashArray[index].value;
            }

            index = getNextCandidateIndex(key, i);
            i++;
        }

        return "Not Found"; // Key not found
    }

    void doubleCapacity()
    {
        int oldCapacity = capacity;
        capacity *= 2;

        HashItem *oldArray = hashArray;
        hashArray = new HashItem[capacity];

        for (int i = 0; i < oldCapacity; ++i)
        {
            if (oldArray[i].status == 2)
            {
                insert(oldArray[i].key, oldArray[i].value);
            }
        }

        delete[] oldArray;
    }

    ~HashMap()
    {
        delete[] hashArray;
    }
};

int main()
{
    HashMap myHashMap(5);

    myHashMap.insert(101, "Alice");
    myHashMap.insert(201, "Bob");
    myHashMap.insert(301, "Charlie");
    myHashMap.insert(401, "David");
    myHashMap.insert(501, "Eva");

    string name = myHashMap.get(201);
    if (!name.empty())
    {
        cout << "Value at key 201: " << name << endl;
    }
    else
    {
        cout << "Key 201 not found!" << endl;
    }

    bool deleted = myHashMap.deleteKey(301);
    if (deleted)
    {
        cout << "Key 301 deleted successfully." << endl;
    }
    else
    {
        cout << "Key 301 not found!" << endl;
    }

    name = myHashMap.get(301);
    if (!name.empty())
    {
        cout << "Value at key 301: " << name << endl;
    }
    else
    {
        cout << "Key 301 not found after deletion." << endl;
    }

    return 0;
}