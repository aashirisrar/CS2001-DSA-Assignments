#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Customer
{
public:
    int customerId;
    int amount;
    int balance;
    string transactionType;

    Customer(int customerId = 0, int amount = 0, int balance = 0, string transactionType = "")
    {
        this->customerId = customerId;
        this->amount = amount;
        this->balance = balance;
        this->transactionType = transactionType;
    }

    void display()
    {
        cout << "---------------------" << endl;
        cout << customerId << endl;
        cout << amount << endl;
        cout << balance << endl;
        cout << transactionType << endl;
    }
};

class Queue
{
    class Node
    {
    public:
        Customer data;
        Node *next;

        Node(int customerId, int amount, int balance, string transactionType)
        {
            data.customerId = customerId;
            data.amount = amount;
            data.balance = balance;
            data.transactionType = transactionType;
            next = NULL;
        }
    };

    Node *front;
    Node *rear;

public:
    Queue()
    {
        front = NULL;
        rear = NULL;
    }

    void enqueue(Customer e)
    {
        Node *newNode = new Node(e.customerId, e.amount, e.balance, e.transactionType);
        if (rear == NULL)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue()
    {

        Node *toDelete = front;
        front = front->next;
        delete toDelete;
    }

    bool isEmpty()
    {
        return front == NULL;
    }

    Customer Front()
    {
        return front->data;
    }

    Customer Rear()
    {
        return rear->data;
    }
};

void enqueueCustomer(Queue &q, Customer data)
{
    q.enqueue(data);
}

int checkBalance(Queue q, stack<Customer> &st, Customer c)
{
    st.push(c);
    return c.balance;
}

void tellerServeCustomer(Queue &q, stack<Customer> &st)
{
    Customer servingCustomer = q.Front();
    q.dequeue();

    // checking what the customer wants to perform
    if (servingCustomer.transactionType == "withdrawl")
    {
        servingCustomer.balance -= servingCustomer.amount;
        st.push(servingCustomer);
    }
    else if (servingCustomer.transactionType == "deposit")
    {
        servingCustomer.balance += servingCustomer.amount;
        st.push(servingCustomer);
    }
    else if (servingCustomer.transactionType == "check_balance")
    {
        cout << "Balance:" << checkBalance(q, st, servingCustomer) << endl;
    }
    else
    {
        cout << "Error!" << endl;
        exit;
    }
}

void getTransactionHistory(stack<Customer> st)
{
    while (!st.empty())
    {
        st.top().display();
        st.pop();
    }
}

int main()
{
    Queue q;
    stack<Customer> st;
    Customer a(2, 89, 100, "withdrawl");
    enqueueCustomer(q, a);
    tellerServeCustomer(q, st);
    getTransactionHistory(st);

    return 0;
}
