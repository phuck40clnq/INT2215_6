#include <iostream>
using namespace std;

void pass(string s)
{
    cout << &s << endl;
}

void pass(int a[])
{
    cout << a << endl;
}

int main()
{
    int a[5] = {1, 2, 3, 4, 5};
    string s = "Hello";
    cout << &a << endl;
    cout << &s << endl;
    pass(a);
    pass(s);
    return 0;
}

// Nhận xét:
// Địa chỉ của mảng a trong main và trong hàm giống nhau -> pass-by-reference
// Địa chỉ của string s trong main và trong hàm khác nhau -> pass-by-value