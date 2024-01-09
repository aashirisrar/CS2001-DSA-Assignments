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
                rear->next = front;
            }
            else
            {
                rear->next = newNode;
                rear = newNode;
                rear->next = front;
            }

            size++;
        }
    }

    void dequeue()
    {
        if (size > 0)
        {
            if (front == rear)
            {
                delete front;
                front = rear = NULL;
            }
            else
            {
                Node *temp = front;
                front = front->next;
                rear->next = front;
                delete temp;
            }

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

    bool isPalindrome()
    {
        Node *temp = front;
        stack<T> st;

        do
        {
            st.push(temp->data);
            temp = temp->next;
        } while (temp != front);

        while (!st.empty())
        {
            if (st.top() == front->data)
            {
                dequeue();
                st.pop();
            }
            else
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(1);

    if (q.isPalindrome())
        cout << "It is a Palidrome!" << endl;
    else
        cout << "Not a Palindrome!" << endl;

    return 0;
}