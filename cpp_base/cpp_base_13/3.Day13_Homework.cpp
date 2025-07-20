#include <iostream>
#include <string.h>
#include <math.h>
#include <sys/wait.h>
#define PI 3.14

using std::endl;
using std::cin;
using std::cout;

class Point 
{
public:
    Point(int ix, int iy)
    : _ix(ix)
    , _iy(iy)
    {}
friend class Line;
private:
    int _ix;
    int _iy;
};

class Color
{
public:
    Color(const char * color) 
    : _color(new char[strlen(color) + 1]())
    {
        strcpy(_color, color);
    }
    
    ~Color() {
        if (_color) {
            delete [] _color;
            _color = nullptr;
        }
    }

    Color(const Color & rhs) 
    : _color(new char[strlen(rhs._color) + 1]())
    {
        strcpy(_color, rhs._color);
    }

    Color & operator=(const Color & rhs) {
        if (this != &rhs) {
            delete _color;
            _color = new char[strlen(rhs._color) + 1]();
            strcpy(_color, rhs._color);
        }
        return *this;
    }

    char * get_color() {
        return _color;
    }

friend class Triangle;    

private:
    char * _color;
};

class Line 
{
public:
    Line(Point & p1, Point & p2) 
    : _p1(p1)
    , _p2(p2)
    {}

    float get_length() {
        return sqrt(pow(_p1._ix - _p2._ix, 2) +  pow(_p1._iy - _p2._iy, 2));
    }
private:
    Point _p1;
    Point _p2;
};

class Triangle 
: public Line
, public Color
{
public:
    Triangle(Point p1, Point p2, const char * color, float height)
    : Line(p1, p2)
    , Color(color)
    , _height(height)
    {
        cout << "Triangle(Point, Point, const char *, float)" << endl;
    }

    float get_third_line() {
        return sqrt(pow(get_length(), 2) + pow(_height, 2));
    }

    float get_Perimeter() {
        return _height + get_length() + get_third_line();
    }

    float get_area() {
        return _height * get_length() / 2;
    }
private:
    float _height;
};

void test() {
    Point p1(1, 3);
    Point p2(4, 7);
    Triangle T(p1, p2, "Green", 3);
    cout << T.get_length() << endl;
    cout << "color: " << T.get_color() << endl;
    cout << "Perimeter: " << T.get_Perimeter() << endl;
    cout << "area: " << T.get_area() << endl;
    
}

int main()
{
    test(); 
    return 0;
}

