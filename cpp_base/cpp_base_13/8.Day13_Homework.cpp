#include <cstdlib>
#include <iostream>
#include <math.h>
#define PI 3.14

using std::cin;
using std::endl;
using std::cout;
using std::string;


class Figure {
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;
};

void display(Figure & fig) {
    cout << fig.getName() 
         << "的面积是:" 
         << fig.getArea() << endl ;
}

class Rectangle 
: public Figure
{
public:
    Rectangle(double length, double width)
    : _length(length)
    , _width(width)
    {}

    virtual string getName() const {
        return string("Rectangle");
    }

    virtual double getArea() const {
        return _length * _width;
    }

private:
    double _length;
    double _width;
};

class Circle 
: public Figure
{
public:
    Circle(double radius)
    : _radius(radius) 
    {}

    virtual string getName() const {
        return string("Circle");
    }

    virtual double getArea() const {
        return PI * _radius * _radius;
    }
private:
    double _radius;
};


class Triangle
: public Figure
{
public:
    Triangle(double side1, double side2, double side3)
    : _side1(side1)
    , _side2(side2)
    , _side3(side3)
    {}

    virtual string getName() const {
        return string("Triangle");
    }

    virtual double getArea() const {
        double p = (_side1 + _side2 + _side3) / 2;
        return sqrt(p * (p - _side1) * (p - _side2) * (p - _side3));
    }

private:
    double _side1;
    double _side2;
    double _side3;
};

void test() {
    Rectangle rec(10, 20);
    Circle cir(5);
    Triangle tri(3, 4, 5);
    Figure * fi = &rec;
    cout << fi->getName() << " " << fi->getArea() << endl;
    fi = &cir;
    cout << fi->getName() << " " << fi->getArea() << endl;
    fi = &tri;
    cout << fi->getName() << " " << fi->getArea() << endl;
}

int main()
{
    test();
    return 0;
}

