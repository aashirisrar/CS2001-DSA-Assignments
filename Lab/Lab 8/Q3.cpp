#include <iostream>
using namespace std;

void subsets(string s, string temp, int index)
{
    if (s.size() == index)
    {
        cout << temp << " ";
        return;
    }

    // take
    subsets(s, temp + s[index], index + 1);

    // not take
    subsets(s, temp, index + 1);
}

int main()
{
    string st = "abcd";

    cout << "Subsets:" << endl;
    subsets(st, "", 0);

    return 0;
}