#include <iostream>
using namespace std;

template <class T>
class Stack
{
    class Node
    {
    public:
        T data;
        Node *next;

        Node(T data)
        {
            this->data = data;
        }
    };

    Node *head;

public:
    Stack()
    {
        head = NULL;
    }

    int size()
    {
        Node *temp = head;
        int count = 0;
        while (temp != NULL)
        {
            temp = temp->next;
            count++;
        }

        return count;
    }

    bool isEmpty()
    {
        if (head == NULL)
        {
            return 0;
        }
        return 1;
    }

    bool Top(T &e)
    {
        if (head != NULL)
        {
            e = head->data;
            return 1;
        }
        return 0;
    }

    void pop()
    {
        Node *temp = head;
        if (head != NULL)
        {
            while (temp->next->next != NULL)
            {
                temp = temp->next;
            }
            Node *toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;

            return;
        }
        cout << "Error! Stack is NULL" << endl;
    }

    void push(T const &element)
    {
        Node *newNode = new Node(element);

        newNode->next = head;
        head = newNode;
    }

    void display()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main()
{
    Stack<int> stack;
    stack.push(5);
    stack.push(4);
    stack.push(3);
    stack.push(2);
    stack.push(1);
    cout << "Original Stack:" << endl;
    stack.display();

    cout << "After one pop:" << endl;
    stack.pop();
    stack.display();

    system("PAUSE");

    return 0;
}