#include <iostream>
using std::endl;
using std::cout;

class Point
{
    public:
        static Point & getInstance() {
            static Point pt(1, 2);
            return pt;
        }

        void print() const {
            cout << "(" << this->_ix
                << "," << this->_iy
                << ")" << endl;
        }

        void init(int x, int y) {
            _ix = x;
            _iy = y;
        }

        Point(const Point &rhs) = delete;
        Point & operator = (const Point & rhs) = delete;
    private:
        Point(int x, int y = 0) 
        :_ix(x)
        ,_iy(y)
        {
               cout << "Point(int, int)" << endl; 
        }

        ~Point() 
        {
            cout << "~Point()" << endl;
        }
        int _ix;
        int _iy;
};

int main() {
    Point & pt = Point::getInstance();
    pt.print();

    Point & pt2 = Point::getInstance();
    pt2.print();
    pt2.init(10, 20);
    pt2.print();

    cout << &pt << endl;
    cout << &pt2 << endl;
    return 0;
}
