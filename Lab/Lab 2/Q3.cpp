#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    int sizeOfArr = arr.size();

    int index = 0;

    bool run = false;

    // Selection Sort
    for (int i = 0; i < sizeOfArr - 1; i++) // n
    {
        int minValue = arr[i]; // n
        run = false;           // n

        for (int j = i + 1; j < sizeOfArr; j++) // n * n
        {
            if (arr[j] < minValue) // n * n
            {
                minValue = arr[j]; // n * n
                index = j;         // n * n
                run = true;        // n * n
            }
        }
        if (run) // n
        {
            int temp = arr[i]; // n
            arr[i] = minValue; // n
            arr[index] = temp; // n
        }
    }

    // Print Array
    for (int i = 0; i < sizeOfArr; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}

// Step Count Analysis T(n) = n + n + n + n^2 + n^2 + n^2 + n^2 + n + n + n + n
//                          = 4n^2 + 7n

// Time Complexity Big-Oh = O(n^2)