#include <iostream>
using namespace std;

int recursiveSum(int n)
{
    if (n != 0)
        return (n % 10 + recursiveSum(n / 10));
    else
        return 0;
}

int main()
{
    int num = 1111;
    cout << "Sum:" << recursiveSum(num) << endl;

    return 0;
}
