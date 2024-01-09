#include <iostream>
using namespace std;

template <class T>
class Queue
{
    class Node
    {
    public:
        T data;
        Node *next;

        Node(T data)
        {
            this->data = data;
            next = NULL;
        }
    };

    Node *front;
    Node *rear;
    int size;

public:
    Queue()
    {
        front = NULL;
        rear = NULL;
        size = 0;
    }

    void enqueue(T ele)
    {
        Node *newNode = new Node(ele);

        if (isEmpty())
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        size++;
    }

    T dequeue()
    {
        if (!isEmpty())
        {
            Node *temp = front;
            T tempData = front->data;
            front = front->next;
            size--;
            delete temp;
            return tempData;
        }
        return T();
    }

    int Size()
    {
        return size;
    }

    bool isEmpty()
    {
        return front == NULL;
    }

    T Front()
    {
        if (!isEmpty())
        {
            return front->data;
        }
        return T();
    }

    T Rear()
    {
        if (!isEmpty())
        {
            return rear->data;
        }
        return T();
    }

    void print()
    {
        Node *temp = front;

        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void eleSort(Queue<T> &, int);

    void RadixSort(T keys[], int n, int k)
    {
        Queue<T> que;

        cout << "Before Sort: ";
        for (int i = 0; i < n; i++)
        {
            cout << keys[i] << " ";
            que.enqueue(keys[i]);
        }

        cout << endl;

        for (int i = 1; i < k + 1; i++)
        {
            cout << "Step " << i << ": ";
            eleSort(que, i);
        }

        for (int i = 0; i < n; i++)
        {
            keys[i] = que.dequeue();
        }
    }

    ~Queue()
    {
        front = NULL;
        rear = NULL;
    }
};

int strSize(string str)
{
    int count = 0;

    while (str[count++] != '\0')
    {
    }

    return count;
}

template <>
void Queue<int>::eleSort(Queue<int> &que, int expo)
{
    const int n = 10; // 10 for integers 0-9

    Queue<int> numQue[n];

    while (!que.isEmpty())
    {
        int currElement = que.dequeue();

        int mul = 1;
        for (int i = 1; i < expo; i++)
        {
            mul = mul * 10;
        }

        int ind = ((currElement) / mul) % 10;
        numQue[ind].enqueue(currElement);
    }

    for (int i = 0; i < n; i++)
    {
        while (!numQue[i].isEmpty())
        {
            que.enqueue(numQue[i].dequeue());
        }
    }

    que.print();
}

template <>
void Queue<string>::eleSort(Queue<string> &que, int expo)
{
    const int n = 26; // 26 for the 26 alphabetic characters

    Queue<string> strQue[n];

    while (!que.isEmpty())
    {
        string item = que.dequeue();
        int sizeStr = strSize(item);

        if (expo > sizeStr)
        {
            strQue[0].enqueue(item);
        }
        else
        {
            int mul = 0;

            while (item[mul + expo] != '\0')
            {
                mul++;
            }

            char temp = item[mul];
            int index = temp - 'a'; // Calculate the index for the character 'a' to 'z'
            strQue[index].enqueue(item);
        }
    }
    for (int i = 0; i < n; i++)
    {
        while (!strQue[i].isEmpty())
        {
            que.enqueue(strQue[i].dequeue());
        }
    }

    que.print();
}

int maxDigits(int numbers[], int count)
{
    int max = 0;

    for (int i = 0; i < count; i++)
    {
        int currentNumber = numbers[i];
        int numDigits = 0;

        while (currentNumber > 0)
        {
            currentNumber = currentNumber / 10;
            numDigits++;
        }

        if (numDigits > max)
        {
            max = numDigits;
        }
    }

    return max;
}

int maxCharacters(string arr[], int count)
{
    int maxLength = 0;

    for (int i = 0; i < count; i++)
    {
        int length = arr[i].length();
        if (length > maxLength)
        {
            maxLength = length;
        }
    }

    return maxLength;
}

int main()
{
    int integerKeys[] = {123, 987, 56, 7890, 345, 654, 1234, 999};

    int n = sizeof(integerKeys) / sizeof(integerKeys[0]);
    int k = maxDigits(integerKeys, n);

    Queue<int> intQue;
    intQue.RadixSort(integerKeys, n, k);

    cout << "After Sorting: ";
    for (int i = 0; i < n; i++)
    {
        cout << integerKeys[i] << " ";
    }

    cout << endl
         << "---------------------------------------------------------" << endl;

    string stringKeys[] = {"fake", "cake", "dusk", "monk", "husk", "lake"};

    n = sizeof(stringKeys) / sizeof(stringKeys[0]);
    k = maxCharacters(stringKeys, n);

    Queue<string> strQue;
    strQue.RadixSort(stringKeys, n, k);

    cout << "After Sorting: ";
    for (int i = 0; i < n; i++)
    {
        cout << stringKeys[i] << " ";
    }

    cout << endl;

    return 0;
}