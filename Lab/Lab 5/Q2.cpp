#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int data) : data(data), next(nullptr) {}
};

class CircularLinkedList
{
private:
    Node *head;

public:
    CircularLinkedList() : head(nullptr) {}

    void insert(int data)
    {
        Node *newNode = new Node(data);
        if (!head)
        {
            head = newNode;
            newNode->next = head;
        }
        else
        {
            Node *temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    void splitEvenOdd(CircularLinkedList &evenList, CircularLinkedList &oddList)
    {
        if (!head)
        {
            return;
        }

        Iterator temp = begin();
        int position = 1;

        do
        {
            if (position % 2 == 0)
            {
                evenList.insert(*temp);
            }
            else
            {
                oddList.insert(*temp);
            }
            ++temp;
            position++;
        } while (temp != head);
    }

    class Iterator
    {
    private:
        Node *current;
        Node *start;

    public:
        Iterator(Node *startNode) : current(startNode), start(startNode) {}

        int operator*()
        {
            return current->data;
        }

        Iterator &operator++()
        {
            current = current->next;
            if (current == start)
            {
                return *this;
            }
            return *this;
        }

        bool operator!=(const Iterator &other)
        {
            return current != other.current;
        }
    };

    Iterator begin()
    {
        return Iterator(head);
    }

    void print()
    {
        Iterator i = begin();

        do
        {
            cout << *i << "->";
            ++i;
        } while (i != begin());

        cout << *i << endl;
    }

    bool search(int val)
    {

        if (head == NULL)
        {
            return 0;
        }

        Iterator i = begin();
        do
        {
            if (*i == val)
                return 1;
            ++i;
        } while (i != begin());

        return 0;
    }

    void insertAtSpecific(int val, int pos)
    {
        Node *temp = head;
        while (pos--)
        {
            temp = temp->next;
        }

        temp->data = val;
    }
};

int main()
{
    CircularLinkedList ll;
    CircularLinkedList evenList;
    CircularLinkedList oddList;

    ll.insert(1);
    ll.insert(2);
    ll.insert(3);
    ll.insert(4);
    ll.insert(5);
    cout << "Original List:" << endl;
    ll.print();

    ll.splitEvenOdd(evenList, oddList);

    cout << "Even-Positioned List: " << endl;
    evenList.print();

    cout << "Odd-Positioned List: " << endl;
    oddList.print();

    int val;
    cout << "Enter a value to search:";
    cin >> val;
    if (ll.search(val))
        cout << "Found!" << endl;
    else
        cout << "Not Found!" << endl;

    cout << "Insertion at Specfic position(inserted 3 at index 4):" << endl;
    ll.insertAtSpecific(3, 4);
    ll.print();

    return 0;
}
