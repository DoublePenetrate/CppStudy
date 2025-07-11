#include <iostream>
using std::cout;
using std::cin;
using std::endl;
class Base
{
public:
    Base(int num)
        : _num(num)
    {}
    friend Base operator+(const Base & lhs, const Base & rhs);
    friend bool operator==(const Base & lhs, int rhs);
private:
    int _num;
};

Base operator+(const Base & lhs, const Base & rhs) {
    return Base(rhs._num - lhs._num);
}

bool operator==(const Base & lhs, int rhs) {
    return lhs._num == rhs;
}

int main()
{
    int i=2;
    int j=7;

    Base x(i);
    Base y(j);
    cout << (x + y == j - i) << endl;
    return 0;
}

