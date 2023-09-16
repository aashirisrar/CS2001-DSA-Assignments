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
    template <class L>
    friend void reverseList(SortedSet<L> &ll);

public:
    SortedSet()
    {
        head = NULL;
        tail = NULL;
    }

    void insertElement(T const data)
    {
        Node<T> *newElement = new Node<T>(data);
        if (newElement == NULL)
        {
            cout << "Error! Memory not Allocated!" << endl;
            return;
        }
        else
        {
            Node<T> *current = head;
            Node<T> *previous = NULL;

            while (current != NULL && current->data <= data)
            {
                if (data == current->data)
                {
                    delete newElement;
                    return;
                }

                previous = current;
                current = current->next;
            }

            newElement->next = current;
            if (head == current)
                head = newElement;
            else
                previous->next = newElement;

            if (current == NULL)
                tail = newElement;
        }
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

    ~SortedSet()
    {
        Node<T> *current = head;
        while (current != NULL)
        {
            Node<T> *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};

template <class T>
void reverseList(SortedSet<T> &ll)
{
    Node<T> *current = ll.head;
    Node<T> *prev = NULL, *next = NULL;

    while (current != NULL)
    {
        // Store next
        next = current->next;
        // Reverse current node's pointer
        current->next = prev;
        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    // Update the head of the SortedSet
    ll.head = prev;
}

int main()
{
    SortedSet<int> ll;
    ll.insertElement(4);
    ll.insertElement(2);
    ll.insertElement(6);
    ll.insertElement(1);
    ll.insertElement(3);
    ll.insertElement(10);
    cout << "First Set:" << endl;
    ll.print();

    cout << "After Reversing:" << endl;
    reverseList(ll);
    ll.print();
    return 0;
}
