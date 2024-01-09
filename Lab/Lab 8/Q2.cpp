#include <iostream>
using namespace std;

void towerOfHanoi(int n, char src, char aux, char dest)
{
    if (n == 1)
    {
        cout << src << " -> " << dest << endl;
        return;
    }

    towerOfHanoi(n - 1, src, dest, aux);
    towerOfHanoi(1, src, aux, dest);
    towerOfHanoi(n - 1, aux, src, dest);
}

int main()
{
    cout << "Moves:" << endl;
    towerOfHanoi(3, 'A', 'B', 'C');

    return 0;
}