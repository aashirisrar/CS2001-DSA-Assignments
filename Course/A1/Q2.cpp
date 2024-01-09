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

    void rotate(int k)
    {
        if (head != NULL && head->next != NULL)
        {
            while (k)
            {
                Node *newHead = head->next;
                head->next = NULL;
                tail->next = head;
                head = newHead;
                tail = tail->next;

                k--;
            }
        }
    }

    ~SortedSet()
    {
        Node *current = head;
        while (current != NULL)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = NULL;
        tail = NULL;
    }
};

int main()
{
    SortedSet<int> ll;
    ll.insertElement(40);
    ll.insertElement(10);
    ll.insertElement(20);
    ll.insertElement(30);
    ll.insertElement(50);
    ll.insertElement(40);
    ll.insertElement(50);
    cout << "Original Set:" << endl;
    ll.print();
    cout << "-------------------------" << endl;

    int k;
    cout << "Enter a value for k:";
    cin >> k;
    while (!k)
    {
        cout << "Error! Enter a valid value for k:";
        cin >> k;
    }
    ll.rotate(k);
    cout << "Set After Rotation:" << endl;
    ll.print();

    return 0;
}
