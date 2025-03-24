#include <iostream>
using namespace std;

void f(int xval)
{
   int x;
   x = xval;
   // in địa chỉ của x tại đây
   cout << &x << endl;
}
void g(int yval)
{
   int y;
   // in địa chỉ của y tại đây
    cout << &y << endl;
}
int main()
{
   f(7);
   g(11);
   return 0;
}

// Nhận xét:
//      Địa chỉ của 2 biến đó trùng nhau 
// Giải thích:
//      Vì 2 biến x và y đều được lưu trữ trong stack chồng lên nhau mỗi lần gọi hàm, nên địa chỉ của 2 biến đó sẽ trùng nhau
