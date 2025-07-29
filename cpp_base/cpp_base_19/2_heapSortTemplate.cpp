#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <math.h>
#include <ostream>


using std::endl;
using std::cout;
using std::vector;
using std::hypot;
using std::ostream;

class Point
{
public:
    Point(int x = 0, int y = 0) 
    : _ix(x)
    , _iy(y)
    {}

    ~Point() {}

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
friend bool operator<(const Point & lhs, const Point & rhs);

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

// 1.模板的特化
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

// 2.针对Point类型 对小于符号进行重载
bool operator<(const Point & lhs, const Point & rhs) {
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

// 3.函数对象版本
struct ComparePoint
{
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
class HeapSorter 
{
private:
    vector<T> _vec;
    void buildHeap(int n, Compare & com);
    void heapify(int n, int i, Compare & com);
public:
    HeapSorter(T * arr, size_t size, Compare com = std::less<T>());
    void heapsort(Compare & com);
    void display();
};

    template<typename T, typename Compare>
HeapSorter<T, Compare>::HeapSorter(T * arr, size_t size, Compare com)
    : _vec(vector<T>(arr, arr + size))
{
    heapsort(com);
}


template<typename T, typename Compare>
void HeapSorter<T, Compare>::heapify(int n, int i, Compare & com) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && com(_vec[largest], _vec[left])) largest = left;
    if (right < n && com(_vec[largest], _vec[right])) largest = right;

    if (largest != i) {
        std::swap(_vec[largest], _vec[i]);
        heapify(n, largest, com);
    }
}

template<typename T, typename Compare>
void HeapSorter<T, Compare>::buildHeap(int n, Compare & com) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(n, i, com);
    }
}

template<typename T, typename Compare>
void HeapSorter<T, Compare>::heapsort(Compare & com) {
    int n = _vec.size();
    /* cout << "n = " << n << endl; */
    buildHeap(n, com);

    for (int i = n - 1; i > 0; i--) {
        std::swap(_vec[i], _vec[0]);
        heapify(i, 0, com);
    }
}


template<typename T, typename Compare>
void HeapSorter<T, Compare>::display() {
    for (auto & elem : _vec) {
        cout << elem << " ";
    }       
    cout << endl;
}

void test1() {
    int arr[10] = {1,3,5,7,9,2,4,6,8,10};
    HeapSorter<int, ComparePoint> hs(arr, 10, ComparePoint());
    hs.display();

}

void test() {
    Point arr[5] = {Point(1,2), Point(3,4), Point(-1,2), Point(4,5), Point(2,5)};
    HeapSorter<Point> hs(arr, 5);
    hs.display();
}

int main()
{
    test();
    return 0;
}

