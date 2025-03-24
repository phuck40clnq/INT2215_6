#include <iostream>
using namespace std;

int factorial(int n)
{
    cout << "n = " << n << " at " << &n << endl;
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

int main()
{
    int n = 5;
    cout << factorial(n) << endl;
    return 0;
}

// Nhận xét:
// Kích thước 1 stack frame là 20 bytes gồm 4 bytes cho biến n và 16 bytes cho return address và frame pointer