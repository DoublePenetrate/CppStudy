#include <iostream>
using std::endl;
using std::cout;

class Point 
{
public:
    static Point * getInstance() {
        if (nullptr == _pInstance) {
            _pInstance = new Point(1, 2);
        }
        return _pInstance;
    }

    void init(int x, int y) {
        _ix = x;
        _iy = y;
    }

    static void destory() {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
            cout << ">> delete heap" << endl;
        }        
    }

    void print() const{
        cout << "(" << this->_ix
            << "," << this->_iy
            << ")" << endl;
    }

private:
    Point(const Point & rhs) = delete;
    Point & operator=(const Point & rhs) = delete;

    Point() = default;
    Point(int x, int y = 0) 
        : _ix(x)
        , _iy(y)
    {
        cout << "Point(int, int)" << endl;
    }

    ~Point() {
        cout << "~Point()" << endl;
    }

private:
    int _ix;
    int _iy;
    static Point * _pInstance;
};
Point * Point::_pInstance = nullptr;

#if 1
void test0(){
    cout << sizeof(Point) << endl;
    Point * p1 = Point::getInstance();
    Point * p2 = Point::getInstance();
    cout << p1 << endl;
    cout << p2 << endl;
    p1->print();
    p2->print();
    /* delete p1; */
    /* p1 = nullptr; */
    /* delete p2; */
    p1->destory();
    p1->destory();
}
#endif

int main() {
    test0();
    Point::getInstance()->print();
    Point::getInstance()->init(10, 20);
    Point::getInstance()->print();

    Point::destory();
    Point::destory();
    Point::destory();
    Point::getInstance()->print();
    Point::destory();

    return 0;
}
