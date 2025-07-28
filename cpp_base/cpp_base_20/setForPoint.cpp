#include <cmath>
#include <iostream>
#include <set>
#include <math.h>

using std::endl;
using std::cin;
using std::cout;
using std::set;
using std::ostream;

template <typename Container>
void display(const Container & con) {
    for (auto & elem : con) {
        cout << elem << " ";
    }
    cout << endl;
}

class Point 
{
public:
    Point(int ix = 0, int iy = 0) 
        : _ix(ix)
          , _iy(iy)
    {
        cout << "Point(int, int)" << endl;
    }

    Point(const Point & rhs) 
        : _ix(rhs._ix)
          , _iy(rhs._iy)
    {
        cout << "Point(const Point &)" << endl;
    }

    float getDistance() const{
        return hypot(_ix,_iy);
    }

    friend class std::less<Point>;
    friend class ComparePoint;
    friend bool operator<(const Point & lhs, const Point & rhs); 
    friend ostream & operator<<(ostream & os, const Point & rhs);
private:
    int _ix;
    int _iy;
};

// 重载输出流运算符
ostream & operator<<(ostream & os, const Point & rhs) {
    os << "(" << rhs._ix 
        << "," << rhs._iy
        << ")";

    return os;
}

// 1.对Key实现小于符号的重载
bool operator<(const Point & lhs, const Point & rhs) 
{
    cout << "bool operator<" << endl;
    if (lhs.getDistance() < rhs.getDistance()) {
        return true;
    } else if (lhs.getDistance() == rhs.getDistance()) {
        if (lhs._ix < rhs._ix) {
            return true;
        } else if (lhs._ix == rhs._ix) {
            if (lhs._iy < rhs._iy) {
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

// 2.实现一个类 用于比较key的大小
class ComparePoint
{
public:
    bool operator()(const Point & lhs, const Point & rhs) const {
        cout << "bool ComaprePoint" << endl;
        if (lhs.getDistance() < rhs.getDistance()) {
            return true;
        } else if (lhs.getDistance() == rhs.getDistance()) {
            if (lhs._ix < rhs._ix) {
                return true;
            } else if (lhs._ix == rhs._ix) {
                if (lhs._iy < rhs._iy) {
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

// 3.将less针对Key进行特化
// 模板的全特化（将模板参数列表中的参数全部以特殊版本的形式展现出来）
namespace std 
{
template <>
struct less<Point> 
{
    bool operator()(const Point & lhs, const Point & rhs) const
    {
        cout << "template <> struct less<Point>" << endl;
        if (lhs.getDistance() < rhs.getDistance()) {
            return true;
        } else if (lhs.getDistance() == rhs.getDistance()) {
            if (lhs._ix < rhs._ix) {
                return true;
            } else if (lhs._ix == rhs._ix) {
                if (lhs._iy < rhs._iy) {
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

void test() {
    set<Point> number = {
        Point(1, 2),
        Point(-1, 2),
        Point(1, -2),
        Point(2, 2),
        Point(1, 2),
        Point(3, 2),
    };
    display(number);
}


int main()
{
    test();
    return 0;
}

