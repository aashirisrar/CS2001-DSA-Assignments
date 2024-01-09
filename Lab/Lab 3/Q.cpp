#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node *next;

	Node(int val)
	{
		data = val;
		next = NULL;
	}
};

template <class T>
class LinkedList
{
public:
	LinkedList()
	{
		head = NULL;
		tail = NULL;
	}
	
	void insertAtHead(T const element)
	{
		Node *temp = new Node(element);

		if (head == NULL)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			temp->next = head;
			head = temp;

			Node *c = head;
			while (c->next != NULL)
			{
				c = c->next;
			}
			tail = c;
		}
	}

	void insertAtTail(T const element)
	{
		Node *temp = new Node(element);

		tail->next = temp;		
		tail = tail->next;
	}

	void Print()
	{
		Node *temp = head;

		while (temp != NULL)
		{
			cout << temp->data << "->";
			temp = temp->next;
		}
		cout <<"NULL"<< endl;
	}

	void eraseAtHead()
	{
		Node *temp = head;
		head = head->next;
		delete temp;
	}

	void eraseAtTail()
	{
		Node *temp = head;

		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = NULL;

		delete tail;
		tail = temp->next;
	}

	void Merge(LinkedList<int> rootSecond)
	{
		this->tail->next = rootSecond.head;
		this->tail = rootSecond.tail;
	}

	void Sort()
	{
		Node *temp = head;

		while (temp->next != NULL)
		{
			if (temp->data > temp->next->data)
			{
				int t = temp->data;
				temp->data = temp->next->data;
				temp->next->data = t;
			}
			temp = temp->next;
		}
	}

	~LinkedList()
	{
		head = NULL;
		tail = NULL;
	}

private:
	Node *head;
	Node *tail;
};

int main()
{
	LinkedList<int> ll;
	ll.insertAtHead(2);
	ll.insertAtHead(1);
	ll.insertAtTail(3);
	ll.Print();

	LinkedList<int> ll2;
	ll2.insertAtHead(4);
	ll2.insertAtHead(5);
	ll2.insertAtTail(6);
	ll2.Print();

	ll.Merge(ll2);
	ll.Print();

	cout << "After Sorting:" << endl;
	ll.Sort();
	ll.Print();

	system("PAUSE");
	return 0;
}