#include <iostream>
using namespace std;

int main()
{
    int x = 0;
    int a[] = {1, 2, 3, 4, 5};
    int y = 0;

    char p = 'a';
    char c[] = {'a', 'b', 'c', 'd', 'e'};
    char q = 'b';

    cout << &x << " " << &a[0] << " " << &a[1] << " " << &a[2] << " " << &y << endl;
    cout << (void*)&p << " " << (void*)&c[0] << " " << (void*)&c[1] << " " << (void*)&c[2] << " " << (void*)&q << endl;
    return 0;
}

// Nhận xét:
// - Địa chỉ của các biến int, mảng int cách nhau 4 bytes
// - Địa chỉ của các biến char, mảng char cách nhau 1 byte
// - Địa chỉ của các biến trước và sau khai báo mảng nằm gần nhau