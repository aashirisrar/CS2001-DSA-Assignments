#include <iostream>
using namespace std;

int GCD(int n1, int n2)
{
    if (n2 == 0)
        return n1;
    else
    {
        return GCD(n2, n1 % n2);
    }
}

int main()
{
    int n1 = 50;
    int n2 = 5;

    cout << "GCD:" << GCD(n1, n2) << endl;

    return 0;
}