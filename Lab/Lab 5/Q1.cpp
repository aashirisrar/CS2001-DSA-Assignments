#include <iostream>
using namespace std;

template <class T>
class DoublyLinkedList
{
    class Node
    {
    public:
        Node *next;
        Node *prev;
        T data;

        Node(T data)
        {
            next = NULL;
            prev = NULL;
            this->data = data;
        }
    };

    Node *head;
    Node *tail;

public:
    DoublyLinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    void insertAtHead(T const element)
    {
        Node *newNode = new Node(element);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
            return;
        }

        newNode->next = head;
        head = newNode;
    }

    void insertAtTail(T const element)
    {
        Node *newNode = new Node(element);
        if (tail == NULL)
        {
            head = newNode;
            tail = newNode;
            return;
        }

        tail->next = newNode;
        newNode->prev = tail;
        tail = tail->next;
    }

    void print()
    {
        Node *temp = head;

        while (temp != NULL)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void deleteAtHead()
    {
        if (head == NULL)
            return;

        Node *toDelete = head;
        head = head->next;
        delete toDelete;
    }

    void deleteAtTail()
    {
        if (tail == NULL)
            return;

        Node *temp = head;

        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }

        Node *toDelete = temp->next;
        tail = temp;
        delete temp;
    }

    void deleteRandom(int pos)
    {
        if (head == NULL)
            return;

        if (pos == 0)
        {
            deleteAtHead();
            return;
        }

        Node *temp = head;
        int count = pos;
        while (count)
        {
            temp = temp->next;
            count--;
        }

        if (temp->next == NULL)
        {
            deleteAtTail();
            return;
        }

        Node *toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }

    void insertSorted(T const element)
    {
        Node *newNode = new Node(element);

        Node *curr, *previous = NULL;
        curr = head;

        while (curr != NULL && curr->data < element)
        {
            previous = curr;
            curr = curr->next;
        }

        newNode->next = curr;
        if (curr == head)
        {
            head = newNode;
        }
        else
        {
            previous->next = newNode;
        }
    }

    void deleteDuplicates()
    {
        Node *temp = head;
        while (temp->next != NULL)
        {
            if (temp->data == temp->next->data)
            {
                Node *toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
            }
            else
            {
                temp = temp->next;
            }
        }
    }

    void swapNodes(int n)
    {
        Node *temp1 = head;
        Node *temp2 = tail;
        int pos = n;
        --pos;
        while (pos)
        {
            temp1 = temp1->next;
            temp2 = temp2->prev;
            pos--;
        }
        Node *temp2Prev = temp2->prev;
        Node *temp2Next = temp2->next;

        Node *temp1Next = temp1->next;
        Node *temp1Prev = temp1->prev;
        temp1Prev->next = temp2;
        temp2->next = temp1Next;

        temp2Prev->next = temp1;
        temp1->next = temp2Next;
    }

    void getNodeFromEnd(int n)
    {
        Node *temp2 = tail;

        int pos = n;
        pos--;
        while (pos)
        {
            temp2 = temp2->prev;
            pos--;
        }
        cout << temp2->data << endl;
    }

    void swap(int *a, int *b)
    {
        int t = *a;
        *a = *b;
        *b = t;
    }

    void Partition(int n)
    {
        Node *temp = head;
        Node *equalHead = NULL, *equalTail = NULL;
        Node *lessHead = NULL, *lessTail = NULL;
        Node *greaterHead = NULL, *greaterTail = NULL;

        while (temp != NULL)
        {
            if (temp->data == n)
            {
                if (equalHead == NULL)
                {
                    equalHead = equalTail = temp;
                }
                else
                {
                    equalTail->next = temp;
                    equalTail = equalTail->next;
                }
            }

            else if (temp->data < n)
            {
                if (lessHead == NULL)
                {
                    lessHead = lessTail = temp;
                }
                else
                {
                    lessTail->next = temp;
                    lessTail = lessTail->next;
                }
            }
            else
            {
                if (greaterHead == NULL)
                {
                    greaterHead = greaterTail = temp;
                }
                else
                {
                    greaterTail->next = temp;
                    greaterTail = greaterTail->next;
                }
            }

            temp = temp->next;
        }

        if (greaterTail != NULL)
        {
            greaterTail->next = NULL;
        }

        if (lessHead == NULL)
        {
            if (equalHead == NULL)
            {
                head = greaterHead;
                return;
            }

            equalTail->next = greaterHead;
            head = equalHead;
            return;
        }

        if (equalHead == NULL)
        {
            lessTail->next = greaterHead;
            head = lessHead;
            return;
        }

        lessTail->next = equalHead;
        equalTail->next = greaterHead;
        head = lessHead;
    }
};

int main()
{
    DoublyLinkedList<int> ll;
    ll.insertAtHead(1);
    ll.insertAtHead(2);
    ll.insertAtTail(3);
    ll.insertAtTail(5);
    ll.insertAtHead(6);
    cout << "Original LL:" << endl;
    ll.print();
    cout << "After Deletion:" << endl;
    ll.deleteRandom(0);
    ll.print();

    cout << "Sorted Linked List:" << endl;
    DoublyLinkedList<int> llSorted;
    llSorted.insertSorted(5);
    llSorted.insertSorted(1);
    llSorted.insertSorted(4);
    llSorted.insertSorted(3);
    llSorted.insertSorted(4);
    llSorted.insertSorted(4);
    llSorted.insertSorted(4);
    llSorted.print();

    cout << "After Removal of Duplicates:" << endl;
    llSorted.deleteDuplicates();
    llSorted.print();

    DoublyLinkedList<int> newLL;
    newLL.insertAtTail(1);
    newLL.insertAtTail(5);
    newLL.insertAtTail(10);
    newLL.insertAtTail(2);
    newLL.insertAtTail(8);
    newLL.insertAtTail(2);
    newLL.insertAtTail(5);
    cout << "New Original:" << endl;
    newLL.print();
    cout << "After Swapping:" << endl;
    newLL.swapNodes(2);
    newLL.print();
    cout << "Get Node From End at 3:" << endl;
    newLL.getNodeFromEnd(3);

    newLL.Partition(5);
    cout << "After Partition at 5:" << endl;
    newLL.print();

    return 0;
}

// 3 -> 5 -> 10 -> 2 -> 8 -> 2 -> 1