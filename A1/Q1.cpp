#include <iostream>
using namespace std;

template <class T>
class SortedSet
{
    struct Node
    {
        T data;
        Node *next;

        Node(T data)
        {
            this->data = data;
            next = NULL;
        }
    };

    Node *head;
    Node *tail;

public:
    SortedSet()
    {
        head = NULL;
        tail = NULL;
    }

    void insertElement(T const data)
    {
        Node *newElement = new Node(data);
        if (newElement == NULL)
        {
            cout << "Error! Memory not Allocated!" << endl;
            return;
        }
        else
        {
            Node *current = head;
            Node *previous;

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
        if (index < 0)
        {
            cout << "Error! Deletion Not Possible, Index Out of Bound: " << index << endl;
            return;
        }

        Node *temp = head;
        if (index == 0)
        {
            Node *toDelete = temp;
            head = head->next;
            delete toDelete;
            return;
        }

        int count = 1;
        while (temp->next != NULL && count < index)
        {
            temp = temp->next;
            count++;
        }

        if (count == index && temp->next != NULL)
        {
            // due to setting the tail at end we have this condition
            tail = temp;
            Node *toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            return;
        }
        else if (temp->next != NULL)
        {
            Node *toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            return;
        }
        cout << "Error! Deletion Not Possible, Index Out of Bound: " << index << endl;
    }

    void print() const
    {
        Node *temp = head;

        while (temp != NULL)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void unionSortedSets(SortedSet<T> const &otherSet)
    {
        Node *firstPtr = head;
        Node *secondPtr = otherSet.head;
        Node *firstNextPtr = firstPtr->next;
        Node *secondNextPtr = secondPtr->next;

        while (firstPtr != NULL && secondPtr != NULL)
        {
            if (firstPtr->data <= secondPtr->data && secondPtr->data <= firstNextPtr->data)
            {
                // check for excluding duplicates
                if (firstNextPtr->data == secondPtr->data)
                {
                    firstNextPtr = firstNextPtr->next;
                    firstPtr = firstPtr->next;
                    secondPtr = secondNextPtr;
                }
                else
                {
                    secondNextPtr = secondPtr->next;
                    firstPtr->next = secondPtr;
                    secondPtr->next = firstNextPtr;

                    // now let curr1 and curr2 to point
                    // to their immediate next pointers
                    firstPtr = secondPtr;
                    secondPtr = secondNextPtr;
                }
            }
            else
            {
                // if more nodes in first list
                if (firstNextPtr->next != NULL)
                {
                    firstNextPtr = firstNextPtr->next;
                    firstPtr = firstPtr->next;
                }

                // else point the last node of first list
                // to the remaining nodes of second list
                else
                {
                    firstNextPtr->next = secondPtr;
                    return;
                }
            }
        }
    }

    ~SortedSet()
    {
        head = NULL;
        tail = NULL;
    }
};

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
    cout << "-------------------------" << endl;
    ll.deleteElement(2);
    cout << "First Set After Deletion:" << endl;
    ll.print();
    cout << "-------------------------" << endl;

    SortedSet<int> ll2;
    ll2.insertElement(3);
    ll2.insertElement(8);
    ll2.insertElement(5);
    ll2.insertElement(9);
    cout << "Second Set:" << endl;
    ll2.print();
    cout << "-------------------------" << endl;

    ll.unionSortedSets(ll2);
    cout << "Union:" << endl;
    ll.print();

    return 0;
}