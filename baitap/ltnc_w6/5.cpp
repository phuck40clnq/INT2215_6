#include <iostream>
using namespace std;

int main()
{
    int a = 10;
    int &r = a;
    cout << "Address of a: " << &a << endl;
    cout << "Address of r: " << &r << endl;

    // int &r2; // Lỗi
    int b = 3;
    // &r = b; // Lỗi
    r = b; // a = r = b = 3
    
    return 0;
}

// Nhận xét:
// - Reference không phải là một đối tượng, nó chỉ là một cái tên khác của một biến đã tồn tại - cùng là 1 biến trong bộ nhớ.
// - Không thể khai báo một reference mà không khởi tạo nó ngay lập tức.
// - Reference không thể thay đổi đối tượng mà nó tham chiếu.