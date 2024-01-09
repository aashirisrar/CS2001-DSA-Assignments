#include <iostream>
#include <queue>
using namespace std;

class StudentMaxHeap;
class Student
{
    friend class StudentMaxHeap;

private:
    double cgpa; // Student’s CGPA
    int rollNo;  // Student’s roll number

public:
    Student(int rollNo = 0, double cgpa = 0)
    {
        this->rollNo = rollNo;
        this->cgpa = cgpa;
    }

    double cgpaGetter()
    {
        return cgpa;
    }

    int rollNoGetter()
    {
        return rollNo;
    }
};
class StudentMaxHeap
{
private:
    Student *st;  // Array of students which will be arranged like a MaxHeap
    int currSize; // Current number of students present in the heap
    int maxSize;  // Maximum no. of students that can be present in heap
public:
    StudentMaxHeap(int size) // Constructor
    {
        currSize = 0;
        maxSize = size;
        st = new Student[size];
    }
    ~StudentMaxHeap()
    {
        delete st;
    }
    bool isEmpty() // Checks whether the heap is empty or not
    {
        return currSize == 0;
    }
    bool isFull() // Checks whether the heap is full or not
    {
        return currSize == maxSize;
    }

    void Swap(Student *st, int parent, int bottom)
    {
        Student temp;

        temp = st[parent];
        st[parent] = st[bottom];
        st[bottom] = temp;
    }

    void ReheapUp(int root, int bottom)
    {
        int parent;
        if (bottom > root)
        { // tree is not empty
            parent = (bottom - 1) / 2;
            if (st[parent].cgpa < st[bottom].cgpa)
            {
                Swap(st, parent, bottom);
                ReheapUp(root, parent);
            }
        }
    }

    bool insert(int rollNo, double cgpa)
    {
        st[currSize++] = Student(rollNo, cgpa);

        ReheapUp(0, currSize - 1);
        return 1;
    }

    void ReheapDown(int root, int bottom)
    {
        int maxChild, rightChild, leftChild;
        leftChild = 2 * root + 1;
        rightChild = 2 * root + 2;
        if (leftChild <= bottom)
        {                            // left child is part of the heap
            if (leftChild == bottom) // only one child

                maxChild = leftChild;

            else
            {

                if (st[leftChild].cgpa <= st[rightChild].cgpa)

                    maxChild = rightChild;

                else

                    maxChild = leftChild;
            }
            if (st[root].cgpa < st[maxChild].cgpa)
            {
                Swap(st, root, maxChild);
                ReheapDown(maxChild, bottom);
            }
        }
    }

    bool removeBestStudent(int &rollNo, double &cgpa)
    {
        rollNo = st[0].rollNo;
        cgpa = st[0].cgpa;

        st[0] = st[currSize - 1];
        currSize--;

        ReheapDown(0, currSize - 1);

        return 1;
    }

    void buildHeap(Student *arr, int n)
    {
        if (n > maxSize)
        {
            cout << "Heap size exceeds the maximum limit." << endl;
            return;
        }

        for (int i = 0; i < n; ++i)
        {
            st[i] = arr[i];
            currSize++;
        }

        for (int i = (currSize / 2) - 1; i >= 0; --i)
        {
            ReheapDown(i, currSize - 1);
        }
    }

    void heapify(int i)
    {
        ReheapUp(i, currSize - 1);
    }

    void print()
    {
        for (int i = 0; i < currSize; i++)
        {
            cout << "CGPA: " << st[i].cgpa << endl;
            cout << "Roll No: " << st[i].rollNo << endl;
        }
    }
};

void heapify(Student *arr, int N, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < N && arr[l].cgpaGetter() > arr[largest].cgpaGetter())
        largest = l;

    if (r < N && arr[r].cgpaGetter() > arr[largest].cgpaGetter())
        largest = r;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, N, largest);
    }
}

void heapSort(Student *st, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(st, n, i);

    // One by one extract an element
    // from heap
    for (int i = n - 1; i > 0; i--)
    {
        // Move current root to end
        swap(st[0], st[i]);

        // call max heapify on the reduced heap
        heapify(st, i, 0);
    }
}

int main()
{
    StudentMaxHeap studentHeap(10); // Increase the size to test heap operations

    studentHeap.insert(22, 3.9);
    studentHeap.insert(23, 3.7);
    studentHeap.insert(18, 2.6);

    cout << "Initial Heap:" << endl;
    studentHeap.print();

    int rollNo;
    double cgpa;
    cout << "Removal of Best Student:" << endl;
    studentHeap.removeBestStudent(rollNo, cgpa);
    cout << "CGPA: " << cgpa << endl;
    cout << "Roll No: " << rollNo << endl;

    cout << "Heap After Removal:" << endl;
    studentHeap.print();

    // Testing heap sort
    Student *students = new Student[5];
    students[0] = Student(22, 3.9);
    students[1] = Student(23, 3.7);
    students[2] = Student(18, 2.6);
    students[3] = Student(25, 3.5);
    students[4] = Student(20, 3.2);

    cout << "Array before heap sort:" << endl;
    for (int i = 0; i < 5; ++i)
    {
        cout << "CGPA: " << students[i].cgpaGetter() << endl;
        cout << "Roll No: " << students[i].rollNoGetter() << endl;
    }

    heapSort(students, 5);

    cout << "Array after heap sort:" << endl;
    for (int i = 0; i < 5; ++i)
    {
        cout << "CGPA: " << students[i].cgpaGetter() << endl;
        cout << "Roll No: " << students[i].rollNoGetter() << endl;
    }

    delete[] students;

    return 0;
}
