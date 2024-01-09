#include <iostream>
using namespace std;

template <class T>
class DoublyLinkedList
{
    class DoublyListNode
    {
    public:
        T data;
        DoublyListNode *next;
        DoublyListNode *prev;

        DoublyListNode(int data)
        {
            this->data = data;
            next = NULL;
            prev = NULL;
        }
    };

    DoublyListNode *head;
    DoublyListNode *tail;

public:
    DoublyLinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    void insertAtHead(T const element)
    {
        DoublyListNode *newNode = new DoublyListNode(element);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertAtTail(T const element)
    {
        DoublyListNode *newNode = new DoublyListNode(element);
        if (tail == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void print() const
    {
        DoublyListNode *temp = head;

        while (temp != NULL)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void printReverse() const
    {
        DoublyListNode *temp = tail;
        while (temp != NULL)
        {
            while (temp != NULL)
            {
                cout << temp->data << "->";
                temp = temp->prev;
            }
            cout << "NULL" << endl;
        }
    }

    void deleteAtStart()
    {
        if (head == NULL)
        {
            return;
        }
        else if (head->next != NULL)
        {
            DoublyListNode *toDelete = head;
            head = head->next;
            head->prev = NULL;
            delete toDelete;
        }
        else
        {
            DoublyListNode *temp = head;

            DoublyListNode *toDelete = temp;
            temp = temp->next;
            head = temp;
            tail = temp;
            delete toDelete;
        }
    }

    void deleteAtTail()
    {
        if (tail == NULL)
        {
            return;
        }
        else if (head->next != NULL)
        {
            DoublyListNode *toDelete = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete toDelete;
        }
        else
        {
            DoublyListNode *temp = head;

            DoublyListNode *toDelete = temp;
            temp = temp->next;
            head = temp;
            tail = temp;
            delete toDelete;
        }
    }

    void deleteAtPosition(int k)
    {
        DoublyListNode *temp = head;
        while (k)
        {
            temp = temp->next;
            k--;
        }

        if (temp->next == NULL)
            deleteAtTail();
        else if (k == 0)
            deleteAtStart();
        else
        {
            DoublyListNode *toDelete = temp;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete toDelete;
        }
    }

    ~DoublyLinkedList()
    {
        DoublyListNode *temp = head;
        while (temp != nullptr)
        {
            DoublyListNode *next = temp->next;
            delete temp;
            temp = next;
        }

        head = NULL;
        tail = NULL;
    }
};

int main()
{
    DoublyLinkedList<int> ll;
    ll.insertAtHead(2);
    ll.insertAtHead(1);
    ll.insertAtHead(3);
    ll.insertAtTail(5);
    ll.insertAtTail(6);
    ll.insertAtHead(8);
    ll.insertAtHead(9);
    cout << "Original Linked List after Insertion:" << endl;
    ll.print();
    cout << "------------------------------------" << endl;
    cout << "Linked List after deletion at Start:" << endl;
    ll.deleteAtStart();
    ll.print();
    cout << "------------------------------------" << endl;
    cout << "Linked List after deletion at Tail:" << endl;
    ll.deleteAtTail();
    ll.print();
    cout << "------------------------------------" << endl;
    cout << "Linked List after deletion at position k:" << endl;
    ll.deleteAtPosition(2);
    ll.print();

    return 0;
}