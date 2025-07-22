#include <iostream>
#include <set>

using std::endl;
using std::cin;
using std::cout;
using std::set;

// 使用函数模板实现两个整数类型数据相加、两个double型数据相加、两个存放int型元素的set融合
template <class T>
T add(T t1, T t2) {
    return t1 + t2;
}

template <>
set<int> add<set<int>>(set<int> lhs, set<int> rhs) {
    set<int> temp = lhs;
    temp.insert(rhs.begin(), rhs.end());
    return temp;
}

void test() {
    int a = 1, b = 2;
    cout << add (a, b) << endl;

    double d1 = 3.14, d2 = 2.71;
    cout << add(d1, d2) << endl;

    set<int> s1 = {1, 3, 5, 7, 9, 10};
    set<int> s2 = {1, 2, 4, 6, 8, 10};
    set<int> res = add(s1, s2);

    for (auto ele : res)
    {
        cout << ele << " ";
    }
    cout << endl;
}

int main()
{
    test();
    return 0;
}

