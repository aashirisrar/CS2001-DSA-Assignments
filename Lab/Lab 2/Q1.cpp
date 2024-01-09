#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> arr = {1, 7, 2, 6, 4, 5};

    for (int i = 0; i < arr.size(); i++) // n
    {
        for (int j = i + 1; j < arr.size(); j++) // n * n
        {
            // Swapping two numbers if the first is greater than the second
            if (arr[i] > arr[j]) // n * n
            {
                int temp = arr[j]; // n * n
                arr[j] = arr[i];   // n * n
                arr[i] = temp;     // n * n
            }
        }
    }

    // Printing the sorted array
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i];
    }

    return 0;
}

// Step Count Analysis T(n) = n + n^2 + n^2 + n^2 + n^2+ n^2 + n + n;
//                          = 5n^2 + n

// Time Complexity Big-Oh = O(n^2)