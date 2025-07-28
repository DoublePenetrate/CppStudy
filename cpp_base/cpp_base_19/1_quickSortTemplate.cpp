#include <cmath>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <ostream>

using std::endl;
using std::cin;
using std::cout;
using std::vector;
using std::ostream;

class Point
{
public:
    Point(int x = 0, int y = 0) 
        : _ix(x)
          , _iy(y)
    {

    }

    ~Point() {

    }

    void display() const {
        cout << "(" << _ix 
            << "," << _iy
            << ")";
    }

    double getDistance() const {
        return hypot(_ix, _iy);
    }

    int getX() const {
        return _ix;
    }

    int getY() const {
        return _iy;
    }

friend ostream & operator<<(ostream & os, const Point & rhs);

private:
    int _ix;
    int _iy;
};

ostream & operator<<(ostream & os, const Point & rhs) {
    cout << "(" << rhs._ix 
        << "," << rhs._iy
        << ")";
    return os;
}

// 1.将类模板less针对Point进行特化
namespace std
{
template<>
    struct less<Point>
{
    bool operator()(const Point & lhs, const Point & rhs) const {
        if(lhs.getDistance() < rhs.getDistance()) {
            return true;
        } else if(lhs.getDistance() == rhs.getDistance()) {
            if(lhs.getX() < rhs.getX()) {
                return true;
            } else if(lhs.getX() == rhs.getX()) {
                if(lhs.getY() < rhs.getY()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};
}
// 2.对小于符号进行运算符重载
bool operator<(const Point & lhs, const Point & rhs) 
{
    if(lhs.getDistance() < rhs.getDistance()) {
        return true;
    } else if(lhs.getDistance() == rhs.getDistance()) {
        if(lhs.getX() < rhs.getX()) {
            return true;
        } else if(lhs.getX() == rhs.getX()) {
            if(lhs.getY() < rhs.getY()) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// 3.使用函数对象的形式
class ComparePoint
{
public:
    bool operator()(const Point & lhs, const Point & rhs) {
        if(lhs.getDistance() < rhs.getDistance()) {
            return true;
        } else if(lhs.getDistance() == rhs.getDistance()) {
            if(lhs.getX() < rhs.getX()) {
                return true;
            } else if(lhs.getX() == rhs.getX()) {
                if(lhs.getY() < rhs.getY()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};

template <typename T, typename Compare = std::less<T>>
class MyQsort
{
public:
    // MyQsort的构造函数
    MyQsort(T *arr, size_t size, Compare comp = std::less<T>()); 
    void quick(int left, int right, Compare & comp);
    int partition(int left, int right, Compare & comp); 
    void print();

private:
    vector<T> _vec;
};

template <typename T, typename Compare>
MyQsort<T, Compare>::MyQsort(T *arr, size_t size, Compare comp) 
    : _vec(vector<T>(arr, arr + size))
{
    quick(0, size - 1, comp);
}

    template <typename T, typename Compare>
void MyQsort<T, Compare>::quick(int left, int right, Compare & comp) 
{
    if (left < right) {
        int pivotIndex = partition(left, right, comp);
        quick(left, pivotIndex - 1, comp);
        quick(pivotIndex + 1, right, comp);
    }
}

    template <typename T, typename Compare>
int MyQsort<T, Compare>::partition(int left, int right, Compare & comp)
{
    T pivot = _vec[left];
    while (left < right) {
        while (left < right && comp(pivot, _vec[right])) right--;
        _vec[left] = _vec[right];
        while (left < right && comp(_vec[left], pivot)) left++;
        _vec[right] = _vec[left];
    }
    _vec[left] = pivot;
    return left;
}

    template <typename T, typename Compare>
void MyQsort<T, Compare>::print()
{
    for (auto & elem : _vec) {
        cout << elem << " ";
    }
    cout << endl;
}

void test1() {
    int arr[10] = {1,3,5,7,9,2,4,6,8,10};
    MyQsort<int> myInt(arr, 10, std::less<int>());
    myInt.print();
}

void test() {
    Point arr[5] = {Point(1,2), Point(3,4), Point(-1,2), Point(4,5), Point(2,5)};
    MyQsort<Point, ComparePoint> myPoint(arr, 5, ComparePoint());
    myPoint.print();
}

int main()
{
    test();
    return 0;
}

