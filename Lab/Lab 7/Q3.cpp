#include <iostream>
#include <stack>
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

    T getMin()
    {
        stack<T> st;
        T min = 999999;

        while (!isEmpty())
        {
            st.push(Front());
            if (st.top() < min)
                min = st.top();

            dequeue();
        }

        while (!st.empty())
        {
            enqueue(st.top());
            st.pop();
        }

        return min;
    }
};

int main()
{
    Queue<int> q;
    q.enqueue(3);
    q.enqueue(2);
    q.enqueue(1);

    cout << "Minimum:" << q.getMin() << endl;

    return 0;
}
