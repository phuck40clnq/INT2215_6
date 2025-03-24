#include <iostream>
#include <vector>
using namespace std;

int BinarySearch(vector<int> &a, int x, int left = 0, int right = -1);

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int x;
    cin >> x;

    int index = BinarySearch(a, x);
    if (index == -1)
    {
        cout << "Not found" << endl;
    }
    else
    {
        cout << "Found at index: " << index << endl;
    }

    return 0;
}

int BinarySearch(vector<int> &a, int x, int left, int right)
{
    if (right == -1)
    {
        right = a.size() - 1;
    }

    if (left > right)
    {
        return -1;
    }

    int mid = left + (right - left) / 2;

    if (a[mid] == x)
    {
        return mid;
    }
    else if (a[mid] > x)
    {
        return BinarySearch(a, x, left, mid - 1);
    }
    else
    {
        return BinarySearch(a, x, mid + 1, right);
    }
}