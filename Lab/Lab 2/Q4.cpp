#include <iostream>
#include <vector>
using namespace std;

int binarySearch(vector<int> arr, int x)
{
    int mid;                // 1
    int l = 0;              // 1
    int h = arr.size() - 1; // 1

    while (l <= h) // lgn
    {
        // Calculating mid
        mid = (l + h) / 2; // lgn

        if (arr[mid] == x) // lgn
        {
            return mid; // lgn
        }

        // Changing mid if arr is greater or less than the element to be found
        if (x > arr[mid]) // lgn
            l = mid + 1;  // lgn
        else
            h = mid - 1;
    }

    return -1; // 1
}

int main()
{
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    int x;
    cout << "Enter the element to search in the array:";
    cin >> x;

    // Sorting Array using bubble sort
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = i + 1; j < arr.size(); j++)
        {
            // swapping two numbers
            if (arr[i] > arr[j])
            {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }

    //  Printing the sorted array
    cout << "Sorted Array:";
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    int num = binarySearch(arr, x);

    if (num != -1)
        cout << "Number found at index " << num << endl;
    else
        cout << "Number not found" << endl;

    return 0;
}

// Step Count Analysis T(n) = 1 + 1 + 1 + logn + logn+ logn+ logn+ logn+ logn + 1
//                          = 6logn + 4

// Time Complexity Big-Oh = O(logn)