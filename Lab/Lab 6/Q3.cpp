#include <iostream>
#include <string>
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
        return head == NULL;
    }

    bool Top(T &e)
    {
        if (head != NULL)
        {
            e = head->data;
            return true;
        }
        return false;
    }

    void pop()
    {
        if (head != NULL)
        {
            Node *toDelete = head;
            head = head->next;
            delete toDelete;
        }
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
    Stack<char> stack;
    string st;
    cout << "Enter a string: ";
    cin >> st;
    bool flag = true;

    for (int i = 0; i < st.length(); i++)
    {
        if (st[i] == ')' || st[i] == '}' || st[i] == ']')
        {
            if (stack.isEmpty())
            {
                flag = false;
                break;
            }

            char top;
            stack.Top(top);

            if ((st[i] == ')' && top == '(') ||
                (st[i] == '}' && top == '{') ||
                (st[i] == ']' && top == '['))
            {
                stack.pop();
            }
            else
            {
                flag = false;
                break;
            }
        }
        else if (st[i] == '(' || st[i] == '{' || st[i] == '[')
        {
            stack.push(st[i]);
        }
    }

    if (!flag || !stack.isEmpty())
    {
        cout << "Not Balanced!" << endl;
    }
    else
    {
        cout << "Balanced!" << endl;
    }

    return 0;
}
