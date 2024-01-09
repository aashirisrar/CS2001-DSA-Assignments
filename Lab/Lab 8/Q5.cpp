#include <iostream>
#include <vector>
using namespace std;

void permutations(vector<int> &arr, vector<vector<int>> &ans, int i)
{
    if (i == arr.size())
    {
        ans.push_back(arr);
        return;
    }

    for (int j = i; j < arr.size(); j++)
    {
        swap(arr[i], arr[j]);
        permutations(arr, ans, i + 1);
        // backtrack
        swap(arr[i], arr[j]);
    }
}

void combinations(vector<int> &elements, vector<int> &data, vector<vector<int>> &ans, int start, int end, int index, int k)
{
    if (index == k)
    {
        ans.push_back(data);
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= k - index; i++)
    {
        data[index] = elements[i];
        combinations(elements, data, ans, i + 1, end, index + 1, k);
    }
}

int main()
{
    vector<int> arr;
    vector<vector<int>> ans;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    permutations(arr, ans, 0);

    cout << "Possible Permutations:" << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    vector<int> combArr;
    vector<vector<int>> ansArr;
    combArr.push_back(1);
    combArr.push_back(2);
    combArr.push_back(3);
    int k = 2;
    vector<int> data(k, 0);
    combinations(combArr, data, ansArr, 0, combArr.size() - 1, 0, k);

    cout << "Possible Combinations:" << endl;
    for (int i = 0; i < ansArr.size(); i++)
    {
        for (int j = 0; j < k; j++)
        {
            cout << ansArr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
