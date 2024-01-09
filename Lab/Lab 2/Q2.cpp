#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    int sizeOfArr = arr.size();

    // Insertion Sort
    for (int i = 1; i < sizeOfArr; i++) // n
    {
        int num = arr[i]; // n
        int j = i - 1;    // n

        while (j >= 0 && arr[j] > num) // n * n
        {
            arr[j + 1] = arr[j]; // n * n
            j--;                 // n * n
        }

        arr[j + 1] = num; // n
    }

    // Print Array
    for (int i = 0; i < sizeOfArr; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}

// Step Count Analysis T(n) = n + n + n + n^2 + n^2 + n^2 + n;
//                          = 3n^2 + 4n

// Time Complexity Big-Oh = O(n^2)
