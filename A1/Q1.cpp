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

    void deleteElement(int const index)
    {
        int count = 1;
        Node<T> *temp = head;

        while (temp->next != NULL && count < index)
        {
            temp = temp->next;
            count++;
        }

        if (index == 0 && temp->next != NULL)
        {
            Node<T> *toDelete = temp;
            head = head->next;
            delete toDelete;
            return;
        }
        else if (count == index)
        {
            tail = temp;
            Node<T> *toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            return;
        }
        else if (temp->next != NULL)
        {
            Node<T> *toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            return;
        }
        cout << "Error! Deletion Not Possible, Index Out of Bound: " << index << endl;
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
        Node<T> *firstPtr = head;
        Node<T> *secondPtr = otherSet.head;

        while (firstPtr != NULL && secondPtr != NULL)
        {
            if (firstPtr->data < secondPtr->data)
            {
                Node<T> *temp = new Node(secondPtr->data);
                temp->next = firstPtr->next;
                firstPtr->next = temp;
                secondPtr = secondPtr->next;
                firstPtr = firstPtr->next;
            }

            firstPtr = firstPtr->next;
        }

        while (secondPtr != NULL)
        {
            Node<T> *temp = new Node(secondPtr->data);
            firstPtr->next = temp;
            secondPtr = secondPtr->next;
            firstPtr = firstPtr->next;
        }
    }

    ~SortedSet()
    {
    }
};

int main()
{
    SortedSet<int> ll;
    ll.insertElement(4);
    ll.insertElement(2);
    ll.insertElement(6);

    ll.print();
    ll.deleteElement(2);
    ll.print();

    // SortedSet<int> ll2;
    // ll2.insertElement(3);
    // ll2.insertElement(8);
    // ll2.insertElement(5);
    // ll2.insertElement(9);

    // ll2.print();

    // ll.unionSortedSets(ll2);
    // ll.print();

    return 0;
}