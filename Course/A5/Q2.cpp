#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

const int PRIME = 11;

template <class v>
struct HashItem
{
    int key;
    v value;
    short status;

    HashItem(int status = 0)
    {
        this->status = status;
    }
};

template <class v>
class HashMap
{
private:
    HashItem<v> *hashArray;
    int capacity;
    int currentElements;
    virtual int getNextCandidateIndex(int key, int i)
    {
        return (key + i) % capacity;
    }

public:
    HashMap()
    {
        capacity = 10;
        currentElements = 0;
        hashArray = new HashItem<v>[capacity];
    }

    HashMap(int const capacity)
    {
        if (capacity > 1)
        {
            currentElements = 0;
            this->capacity = capacity;
            hashArray = new HashItem<v>[capacity];

            return;
        }

        cout << "Error! (capacity should greater than 1)!";
        exit(0);
    }

    void insert(int const key, v const value)
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
                hashArray[index].status = 1;
                currentElements--;
                return true;
            }

            index = getNextCandidateIndex(key, i);
            i++;
        }

        return false;
    }

    v *get(int const key)
    {
        int index = key % capacity;
        int i = 1;

        while (hashArray[index].status != 0)
        {
            if (hashArray[index].key == key && hashArray[index].status == 2)
            {
                return &(hashArray[index].value);
            }

            index = getNextCandidateIndex(key, i);
            i++;
        }

        return NULL;
    }

    void doubleCapacity()
    {
        int oldCap = capacity;
        capacity = capacity * 2;

        HashItem<v> *oldArr = hashArray;
        hashArray = new HashItem<v>[capacity];

        for (int i = 0; i < oldCap; ++i)
        {
            if (oldArr[i].status == 2)
            {
                insert(oldArr[i].key, oldArr[i].value);
            }
        }

        delete[] oldArr;
    }

    int getCapacity() const
    {
        return capacity;
    }

    ~HashMap()
    {
        delete[] hashArray;
    }
};

template <class v>
class DHashMap : public HashMap<v>
{
    int getNextCandidateIndex(int key, int i)
    {
        return (key + (i * i)) % HashMap<v>::getCapacity();
    }
};

template <class v>
class QHashMap : public HashMap<v>
{
    int getNextCandidateIndex(int key, int i)
    {
        int first = key % HashMap<v>::getCapacity();
        int second = (PRIME - (key % PRIME));
        return (first + (i * second)) % HashMap<v>::getCapacity();
    }
};

void populateHash(string filename, HashMap<string> *hashM)
{
    ifstream f(filename);

    if (f.is_open())
    {
        string l;
        while (getline(f, l))
        {
            stringstream ss(l);
            int id;
            string name;

            if (ss >> id >> name)
            {
                hashM->insert(id, name);
            }
            else
            {
                cout << "Error reading the line: " << l << endl;
                exit(0);
            }
        }

        f.close();
    }
    else
    {
        cout << "Unable to open the file: " << filename << endl;
        exit(0);
    }
}

int main()
{
    HashMap<string> *map;
    map = new HashMap<string>;
    populateHash("students.txt", map);
    cout << *map->get(9);
    map->deleteKey(9);
    assert(map->get(9) == NULL);
    delete map;
    map = new QHashMap<string>;
    populateHash("students.txt", map);
    cout << *map->get(98);
    map->deleteKey(98);
    assert(map->get(98) == NULL);
    delete map;
    map = new DHashMap<string>;
    populateHash("students.txt", map);
    cout << *map->get(101);
    map->deleteKey(101);
    assert(map->get(101) == NULL);
    delete map;
    return 0;
}