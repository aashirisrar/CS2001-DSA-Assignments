#include <iostream>
#include <string>
using namespace std;

template <class T>
class Dequeue
{
    class Node
    {
    public:
        T data;
        Node *next;
        Node(T data)
        {
            this->data = data;
            next = NULL;
        }
    };
    Node *front;
    Node *rear;
    int size;

public:
    Dequeue()
    {
        front = NULL;
        rear = NULL;
        size = 0;
    }

    void enqueue(T e)
    {
        Node *newNode = new Node(e);
        size++;
        if (front == NULL)
        {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    void dequeue()
    {
        if (front != NULL)
        {
            Node *toDelete = front;
            front = front->next;
            delete toDelete;
            size--;
        }
    }

    void pop()
    {
        if (front != NULL)
        {
            if (front == rear)
            {
                delete front;
                front = rear = NULL;
                size = 0;
            }
            else
            {
                Node *temp = front;
                while (temp->next != rear)
                {
                    temp = temp->next;
                }
                Node *toDelete = rear;
                rear = temp;
                rear->next = NULL;
                delete toDelete;
                size--;
            }
        }
    }

    T Rear()
    {
        return rear->data;
    }

    bool empty()
    {
        return size == 0;
    }

    int Size()
    {
        return size;
    }

    ~Dequeue()
    {
        while (front != NULL)
        {
            Node *toDelete = front;
            front = front->next;
            delete toDelete;
        }
        rear = NULL;
        size = 0;
    }
};

template <class D>
class UndoStack
{
    Dequeue<D> elements;

public:
    void push(const D &element)
    {
        if (elements.Size() >= 100)
        {
            elements.dequeue();
        }
        elements.enqueue(element);
    }

    D pop()
    {
        if (!elements.empty())
        {
            D topElement = elements.Rear();
            elements.pop();
            return topElement;
        }
        cout << "Stack is empty" << endl;
        return 0;
    }

    bool empty()
    {
        return elements.empty();
    }

    int size()
    {
        return elements.Size();
    }
};

int main()
{
    UndoStack<int> undoStack;

    // Pushing 120 elements
    for (int i = 0; i <= 120; i++)
    {
        undoStack.push(i);
    }

    // Undo last 10 operations
    for (int i = 0; i < 10; i++)
    {
        if (!undoStack.empty())
        {
            cout << "Undo: " << undoStack.pop() << endl;
        }
        else
        {
            cout << "UndoStack is empty." << endl;
        }
    }

    return 0;
}
