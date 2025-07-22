#include <iostream>

using std::endl;
using std::cin;
using std::cout;

//递归的出口
void print() {
    cout << endl;
}   

//重新定义一个可变参数模板，至少得有一个参数
template <class T, class ...Args>
void print(T x, Args ...args) 
{
    cout << x << endl;
    print(args...);
}

void test() {
    print();
    cout << "-----------" << endl;
    print(2.3, 2, 78, "hello", true);
    cout << "-----------" << endl;

}

int main()
{
    test();
    return 0;
}

