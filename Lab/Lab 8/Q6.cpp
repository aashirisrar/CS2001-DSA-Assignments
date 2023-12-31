#include <iostream>
using namespace std;

bool isSafe(int **arr, int x, int y, int n)
{
    for (int row = 0; row < x; row++)
    {
        if (arr[row][y] == 1)
            return 0;
    }

    int row = x;
    int col = y;

    while (row >= 0 && col >= 0)
    {
        if (arr[row][col] == 1)
            return 0;

        row--;
        col--;
    }

    row = x;
    col = y;

    while (row >= 0 && col < n)
    {
        if (arr[row][col] == 1)
            return 0;

        row--;
        col++;
    }

    return 1;
}

bool nQueen(int **arr, int x, int n)
{
    if (x >= n)
        return 1;

    for (int col = 0; col < n; col++)
    {
        if (isSafe(arr, x, col, n))
        {
            arr[x][col] = 1;

            if (nQueen(arr, x + 1, n))
            {
                return 1;
            }

            // backtrack
            arr[x][col] = 0;
        }
    }

    return 0;
}

int main()
{
    int n;
    cout << "Enter a value for n:";
    cin >> n;

    int **arr = new int *[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[n];

        for (int j = 0; j < n; j++)
        {
            arr[i][j] = 0;
        }
    }

    if (nQueen(arr, 0, n))
    {
        cout << "Solution:" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        return 0;
    }
    else
    {
        cout << "No solution!" << endl;
    }

    return 0;
}