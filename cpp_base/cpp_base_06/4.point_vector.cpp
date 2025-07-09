#include <cstddef>
#include <iostream>
#include <vector>
using std::endl;
using std::cout;
using std::cin;
using std::vector;

class Point 
{
public:
    Point(int x = 0, int y = 0) 
    : _ix(x)
    , _iy(y)
    {
        //cout << "Point(int, int)" << endl;
    }

    ~Point() 
    {
        //cout << "~Point()" << endl;
    }

    Point(const Point & rhs) 
    : _ix(rhs._ix)
    , _iy(rhs._iy)
    {
        //cout << "Point(const Point &)" << endl;
    }

    Point & operator=(const Point & rhs) {
        _ix = rhs._ix;
        _iy = rhs._iy;
        //cout << "operator=(const Point &)" << endl;
        return *this;
    }

    void print() {
        cout << "(x, y) = " << "(" << _ix << ", " << _iy << ")" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test1() {
    vector<Point> vec;
    vec.reserve(10);
    vec.push_back(Point(1, 2));
    vec.push_back(Point(3, 4));
    vec.push_back(Point(5, 6));
    vec.push_back(Point(4, 8));
    cout << "vec's size is " << vec.size() << endl;
    for (auto ele : vec) {
        ele.print();
    }
    cout << "-----------------------" << endl;

    for (vector<Point>::iterator it = vec.begin(); it != vec.end(); it++) {
        it->print();
    }
}


int main() {
    test1();
    return 0;
}
