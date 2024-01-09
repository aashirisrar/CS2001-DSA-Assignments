#include <iostream>

using namespace std;

class IntervalHeap
{
private:
    int hsize;   
    int maxsize; 
    int** h;     
    bool flag = false;

public:
    IntervalHeap(int s = 100)
    {
        maxsize = s;
        hsize = 0;
        h = new int* [2];
        h[0] = new int[maxsize];
        h[1] = new int[maxsize]; 
    }

    void Insert(int d)
    {
        if (h[0][hsize] == h[1][hsize] && !flag)
        {
            h[0][hsize] = d;
            h[1][hsize] = d;
            flag = true;
            return;
        }

        if (h[0][hsize] < d)
        {
            h[1][hsize] = d;
        }
        else
        {
            h[0][hsize] = d;
        }

        // Maintain the heap properties
        flag = false;
        ReheapUpMin(0, hsize);
        ReheapUpMax(0, hsize);
        hsize++;
    }

    void ReheapUpMin(int root, int size)
    {
        int parent;
        if (root < size)
        {
            parent = (size - 1) / 2;
            if (h[0][parent] > h[0][size])
            {
                swap(h[0][parent], h[0][size]);
                ReheapUpMin(root, parent);
            }
        }
    }

    void ReheapUpMax(int root, int size)
    {
        int parent;
        if (root < size)
        {
            parent = (size - 1) / 2;
            if (h[1][parent] < h[1][size])
            {
                swap(h[1][parent], h[1][size]);
                ReheapUpMax(root, parent);
            }
        }
    }

    void ReheapDownMin(int root, int bottom)
    {
        int maxChild, rightChild, leftChild;
        leftChild = 2 * root + 1;
        rightChild = 2 * root + 2;
        if (leftChild <= bottom)
        {                            
            if (leftChild == bottom) 

                maxChild = leftChild;

            else
            {
                if (h[0][leftChild] >= h[0][rightChild])

                    maxChild = rightChild;

                else

                    maxChild = leftChild;
            }
            if (h[0][root] > h[0][maxChild])
            {
                swap(h[0][root], h[0][maxChild]);
                ReheapDownMin(maxChild, bottom);
            }
        }
    }

    void ReheapDownMax(int root, int bottom)
    {
        int maxChild, rightChild, leftChild;
        leftChild = 2 * root + 1;
        rightChild = 2 * root + 2;
        if (leftChild <= bottom)
        {                            
            if (leftChild == bottom) 

                maxChild = leftChild;

            else
            {
                if (h[1][leftChild] <= h[1][rightChild])

                    maxChild = rightChild;

                else

                    maxChild = leftChild;
            }
            if (h[1][root] < h[1][maxChild])
            {
                swap(h[1][root], h[1][maxChild]);
                ReheapDownMax(maxChild, bottom);
            }
        }
    }

    void Delete()
    {
        h[0][0] = h[0][hsize - 1];
        h[1][0] = h[1][hsize - 1];
        hsize--;
        ReheapDownMin(0, hsize);
        ReheapDownMax(0, hsize);
    }

    void Display()
    {
        cout << "Interval Heap:" << endl;
        for (int i = 0; i < hsize; i++)
        {
            cout << "[" << h[0][i] << ", " << h[1][i] << "] ";
        }
        if (flag == true)
        {
            cout << "[" << h[0][hsize] << ", " << h[1][hsize] << "] ";
        }
        cout << endl;
    }
};

int main()
{
    IntervalHeap intervalHeap;

    // Insert elements 
    intervalHeap.Insert(50);
    intervalHeap.Insert(25);
    intervalHeap.Insert(55);
    intervalHeap.Insert(30);
    intervalHeap.Insert(40);
    intervalHeap.Insert(60);
    intervalHeap.Insert(70);
    intervalHeap.Insert(20);
    intervalHeap.Insert(45);
    intervalHeap.Insert(65);

    // Display the interval heap
    intervalHeap.Display();

    intervalHeap.Delete();

    intervalHeap.Display();

    return 0;
}

