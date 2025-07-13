#include <iostream>
#include <ostream>

using std::endl;
using std::cout;
using std::cin;
using std::ostream;

class Point
{
public:
    Point(int x, int y) 
    : _x(x)
    , _y(y)
    {}

friend ostream & operator<<(ostream & os, const Point & rhs);

private:
    int _x;
	int _y;
};

ostream & operator<<(ostream & os, const Point & rhs) {
    os << "(" << rhs._x << "," << rhs._y << ")";
    return os;
}

void test0(){
    Point pt(1,2);
    cout << pt << endl; //本质形式： operator<<(cout,pt) << endl;
}

int main()
{
    test0();
    return 0;
}

