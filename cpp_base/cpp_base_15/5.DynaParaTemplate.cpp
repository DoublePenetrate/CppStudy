#include <iostream>

using std::endl;
using std::cin;
using std::cout;

// 利用可变模板参数实现一个函数模板，用来计算多个整型、浮点型数据的加法
double add() {
    return 0;
}

template <class T, class ...Args>
double add(T x, Args ...args) 
{
    return x + add(args...);
}

void test() {
    double res = add(1, 3.14, 5, 100, 10.18);
    cout << res << endl;
}


int main()
{
    test();
    return 0;
}

