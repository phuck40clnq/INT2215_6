#include <iostream>
using namespace std;

void passbyvalue(int x)
{
    cout << "Address of x in function: " << &x << endl;
}

int main()
{
    int x = 10;
    cout << "Address of x in main: " << &x << endl;
    passbyvalue(x);
    return 0;
}

// Nhận xét:
// - Địa chỉ của biến x trong hàm main và hàm passbyvalue là khác nhau.