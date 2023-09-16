#include <iostream>
using namespace std;

template <class D>
struct Node
{
    D data;
    Node *next;

    Node(D data)
    {
        this->data = data;
        next = NULL;
    }
};

template <class T>
class SortedSet
{
    Node<T> *head;
    Node<T> *tail;

public:
    SortedSet()
    {
        head = NULL;
        tail = NULL;
    }

    void insertElement(T const data)
    {
        Node<T> *newElement = new Node(data);
        if (newElement == NULL)
        {
            cout << "Error! Memory not Allocated!" << endl;
            return;
        }
        else
        {
            Node<T> *current = head;
            Node<T> *previous;

            while (current != NULL && current->data < data)
            {
                previous = current;
                current = current->next;
            }

            newElement->next = current;
            if (head == current)
            {
                head = newElement;
            }
            else
            {
                previous->next = newElement;
            }
        }
    }

    void deleteElement(int const index)
    {
    }

    void print() const
    {
        Node<T> *temp = head;

        while (temp != NULL)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void unionSortedSets(SortedSet<T> const &otherSet)
    {
    }

    ~SortedSet()
    {
    }
};

int main()
{
    SortedSet<int> ll;
    ll.insertElement(3);
    ll.insertElement(2);
    ll.insertElement(5);
    ll.insertElement(4);
    ll.insertElement(1);
    ll.print();

    return 0;
}