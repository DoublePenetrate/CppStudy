#include <iostream>
#include <math.h>
using std::endl;
using std::cout;
using std::cin;

class Point 
{
public:
    Point(int x, int y) 
    : _ix(x)
    , _iy(y)
    {}

    friend float distance(const Point & lhs, const Point & rhs);
private:
    int _ix;
    int _iy;
};

float distance(const Point & lhs, const Point & rhs) {
    return sqrt(pow(lhs._ix - rhs._ix, 2) + pow(lhs._iy - rhs._iy, 2));
}

int main()
{
    // 1.友元的使用=>普通函数
    Point p1(3, 7);
    Point p2(6, 3);
    cout << distance(p1, p2) << endl;
    return 0;
}

