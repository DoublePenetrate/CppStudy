#include <iostream>

using std::endl;
using std::cin;
using std::cout;

class Point
{
public:
    Point(double x,double y)
        : _x(x)
          , _y(y)
    {}

    template <class T>
        T add(T t1);
private:
    double _x;
    double _y;
};

template <class T>
T Point::add(T t1)
{
    return _x + _y + t1;
}

void test0(){
    Point pt(1.5,3.8);
    cout << pt.add(8.8) << endl;
}

int main()
{
    test0();
    return 0;
}

