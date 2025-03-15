#include <iostream>
using namespace std;

// Hàm xử lý xâu
int my_strlen(char a[]);

// Hàm đảo ngược thứ tự của a
void reverse(char a[]);

// Hàm xóa hết các kí tự c trong xâu a
void delete_char(char a[], char c);

// Hàm độn thêm các kí tự space vào cuối xâu a để a có độ dài bằng n. Nếu a đã dài quá n thì không phải làm gì cả
void pad_right(char a[], int n);

// Hàm độn thêm các kí tự space vào đầu xâu a để a có độ dài bằng n. Nếu a đã dài quá n thì không phải làm gì cả
void pad_left(char a[], int n);

// Hàm cắt bớt đoạn cuối của xâu a để a có độ dài n nếu như a đang dài quá n kí tự
void runcate(char a[], int n);

// Hàm kiểm tra xem xâu a có đối xứng hay không. Trả về true nếu đối xứng, false nếu không
bool is_palindrome(char a[]);

// Hàm xóa các kí tự trắng đứng ở đầu xâu a, nếu có
void trim_left(char a[]);

// Hàm xóa các kí tự trắng đứng ở cuối xâu a, nếu có
void trim_right(char a[]);

int main()
{
    char a[] = "hello";
    reverse(a);
    cout << a << endl;

    char b[] = "hello";
    delete_char(b, 'l');
    cout << b << endl;

    char c[20] = "hello";
    pad_right(c, 10);
    cout << c << endl;

    char d[20] = "hello";
    pad_left(d, 10);
    cout << d << endl;

    char e[] = "hello";
    runcate(e, 3);
    cout << e << endl;

    char f[] = "abba";
    cout << is_palindrome(f) << endl;

    char g[] = "   hello";
    trim_left(g);
    cout << g << endl;

    char h[] = "hello   ";
    trim_right(h);
    cout << h << endl;

    // Success
    return 0;
}

int my_strlen(char a[])
{
    int i = 0;
    while (a[i] != '\0')
    {
        i++;
    }
    return i;
}

void reverse(char a[])
{
    int l = my_strlen(a);
    for (int i = 0; i < l / 2; i++)
    {
        char tmp = a[i];
        a[i] = a[l - i - 1];
        a[l - i - 1] = tmp;
    }
}

void delete_char(char a[], char c)
{
    char* p = a;
    char* tmp = a;
    
    while (*tmp != '\0')
    {
        if (*tmp != c)
        {
            *p = *tmp;
            p++;
        }
        tmp++;
    }

    *p = '\0';
}

void pad_right(char a[], int n)
{
    int l = my_strlen(a);
    if (l >= n)
    {
        return;
    }

    for (int i = l; i < n; i++)
    {
        a[i] = ' ';
    }
    a[n] = '\0';
}

void pad_left(char a[], int n)
{
    int l = my_strlen(a);
    if (l >= n)
    {
        return;
    }

    for (int i = n - 1; i >= n - l; i--)
    {
        a[i] = a[i - n + l];
    }

    for (int i = 0; i < n - l; i++)
    {
        a[i] = ' ';
    }
}

void runcate(char a[], int n)
{
    int l = my_strlen(a);
    if (l <= n)
    {
        return;
    }

    a[n] = '\0';
}

bool is_palindrome(char a[])
{
    int l = my_strlen(a);
    for (int i = 0; i < l / 2; i++)
    {
        if (a[i] != a[l - i - 1])
        {
            return false;
        }
    }
    return true;
}

void trim_left(char a[])
{
    int l = my_strlen(a);
    int i = 0;
    while (a[i] == ' ')
    {
        i++;
    }

    for (int j = 0; j < l - i; j++)
    {
        a[j] = a[j + i];
    }
    a[l - i] = '\0';
}

void trim_right(char a[])
{
    int i = my_strlen(a) - 1;
    while (a[i] == ' ')
    {
        i--;
    }

    a[i + 1] = '\0';
}