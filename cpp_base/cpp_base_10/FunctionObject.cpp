#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class FunctionObject
{
public:
    void operator()() {
        cout << "FunctionObject operator()" << endl;
        ++_count;
    }

    int operator()(int lhs, int rhs) {
        cout << "int operator(int, int)" << endl;
        ++_count;
        return lhs + rhs;
    }

    int _count = 0;
};

void test() {
    FunctionObject fo;
  
    fo();
    fo.operator()();//本质

    cout << fo(5,6) << endl;
    cout << fo.operator()(5,6) << endl;//本质

    cout << "fo._count:" << fo._count << endl;//记录这个函数对象被调用的次数
}

int main()
{
    test();
    return 0;
}

