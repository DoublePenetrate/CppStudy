#include <iostream>
#include <math.h>
using std::cout;
using std::cin;
using std::endl;

class Point
{

friend class Line;
public:
    Point(int x, int y) 
    : _ix(x)
    , _iy(y)
    {}


private:
    int _ix;
    int _iy;
};

class Line
{
public:
    float distance(const Point & lhs, const Point & rhs) {
        return sqrt(pow(lhs._ix - rhs._ix, 2) + pow(lhs._iy - rhs._iy, 2));
}
};

int main()
{
    // 3.友元的使用=>友元类  
    Point p1 = Point(0, 3);
    Point p2 = Point(3, 7);
    Line ll;
    cout << ll.distance(p1, p2) << endl;
    return 0;
}

