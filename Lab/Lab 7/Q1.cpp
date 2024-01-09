#include <iostream>
using namespace std;

template <class T>
class Queue
{
    class Node
    {
    public:
        T data;
        Node *next;

        Node(int data)
        {
            this->data = data;
            next = NULL;
        }
    };

    int size;
    int maxSize;
    Node *front;
    Node *rear;

public:
    Queue()
    {
        front = NULL;
        rear = NULL;
        size = 0;
        maxSize = 100;
    }

    void enqueue(T e)
    {
        if (size < maxSize)
        {
            Node *newNode = new Node(e);
            if (rear == NULL)
            {
                front = rear = newNode;
            }
            else
            {
                rear->next = newNode;
                rear = newNode;
            }

            size++;
        }
    }

    void dequeue()
    {
        if (size > 0)
        {
            Node *toDelete = front;
            front = front->next;
            delete toDelete;
            size--;
        }
    }

    bool isFull()
    {
        return size == maxSize;
    }

    int Size()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    T Front()
    {
        return front->data;
    }

    T Rear()
    {
        return rear->data;
    }
};

int main()
{
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    q.dequeue();

    if (q.isFull())
    {
        cout << "Queue is Full" << endl;
    }
    else
    {
        cout << "Queue is not Full" << endl;
    }

    cout << "Size of Queue:";
    cout << q.Size();

    if (q.isEmpty())
    {
        cout << "\nQueue is empty" << endl;
    }
    else
    {
        cout << "\nQueue is not empty" << endl;
    }

    cout << "Front:" << q.Front();
    cout << "\nRear:" << q.Rear() << endl;

    return 0;
}
