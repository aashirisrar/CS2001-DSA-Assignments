#include <iostream>
using namespace std;

template <class T>
class Stack
{
    T *arr;
    int capacity;
    int size;
    int top;
    int rear;
    bool flag;

public:
    Stack(int initialCapacity = 10)
    {
        capacity = initialCapacity;
        arr = new T[capacity];
        size = 0;
        top = -1;
        rear = 0;
        flag = false;
    }

    void push(int e)
    {
        if (size == capacity)
        {
            // If the stack is full, doubling the capacity
            int newCapacity = capacity * 2;
            T *newArr = new T[newCapacity];

            // Copy elements to the new array in the circular way
            for (int i = 0; i < size; i++)
            {
                newArr[i] = arr[(rear + i) % capacity];
            }

            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
            rear = 0;
            top = size - 1;
        }

        if (!flag)
        {
            top = (top + 1) % capacity;
            arr[top] = e;
        }
        else
        {
            rear = (rear - 1 + capacity) % capacity;
            arr[rear] = e;
        }
        size++;
    }

    void pop()
    {
        if (size > 0)
        {
            if (!flag)
            {
                top = (top - 1 + capacity) % capacity;
            }
            else
            {
                rear = (rear + 1) % capacity;
            }
            size--;

            // If the stack becomes less than half full, halving the capacity
            if (size <= capacity / 2 && capacity > 2)
            {
                int newCapacity = capacity / 2;
                T *newArr = new T[newCapacity];

                // Copy elements to the new array in a circular way
                for (int i = 0; i < size; i++)
                {
                    newArr[i] = arr[(rear + i) % capacity];
                }

                delete[] arr;
                arr = newArr;
                capacity = newCapacity;
                rear = 0;
                top = size - 1;
            }
        }
    }

    void flipStack()
    {
        // Reversing logical order of stack using the flag variable
        flag = !flag;
    }

    T Top()
    {
        if (size > 0)
        {
            return flag ? arr[rear] : arr[top];
        }
        else
        {
            cout << "Stack is empty." << endl;
            return -1;
        }
    }

    void display()
    {
        if (size > 0)
        {
            if (!flag)
            {
                int index = top;
                for (int i = 0; i < size; i++)
                {
                    cout << arr[index] << " ";
                    index = (index - 1 + capacity) % capacity;
                }
            }
            else
            {
                int index = rear;
                for (int i = 0; i < size; i++)
                {
                    cout << arr[index] << " ";
                    index = (index + 1) % capacity;
                }
            }
            cout << endl;
        }
        else
        {
            cout << "Stack is empty." << endl;
        }
    }

    ~Stack()
    {
        delete[] arr;
    }
};

int main()
{
    Stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);

    // left=top ------ right=rear (5 4 3 2 1)
    cout << "Original Stack:" << endl;
    st.display();

    st.pop();
    cout << "After 1st pop:" << endl;
    st.display();

    cout << "After 1st Flip:" << endl;
    st.flipStack();
    st.display();

    st.push(4);
    cout << "After Push:" << endl;
    st.display();

    st.pop();
    cout << "After 2nd pop:" << endl;
    st.display();

    cout << "After 2nd Flip:" << endl;
    st.flipStack();
    st.display();

    return 0;
}
