#include <iostream>
#include <list>

using std::endl;
using std::cin;
using std::cout;
using std::list;

template <typename Container>
void display(const Container & con) {
    for (auto & elem : con) {
        cout << elem << " ";
    }
    cout << endl;
}

template <typename T>
class compareList
{
public:
    bool operator() (const T & lhs, const T & rhs) {
        return lhs > rhs;
    }

};

void test1() {
    list<int> number({1,3,5,7,9,2,4,6,8,10});
    /* list<int> number = {1,3,5,7,9,2,4,6,8,10}; */
    // 1. 逆置list
    number.reverse();
    display(number);

    // 2. list排序
    // 默认sort排序是从小到大
    number.sort();
    display(number);
    number.sort(std::greater<int>());
    display(number);
    number.sort(compareList<int>());
    display(number);
}

void test() {
    // 3.unique函数 去除重复元素
    list<int> number = {1,3,5,3,6,3,5,5,5,8,3,3};
    number.sort(std::less<int>());
    number.unique();
    /* display(number); */

    // 4.merge函数 合并两个list
    list<int> other = {11, 55, 44, 33, 22, 6};
    /* other.sort(std::less<int>()); */
    /* number.merge(other); */
    /* display(number); */

    // 5.splice函数
    auto it = number.begin();
    // 5.1 将other链表全部转移到it之前
    /* number.splice(it, other); */
    
    // 5.2 将other链表中一个元素转移到it之前
    auto it2 = other.end();
    /* it2--; */
    /* number.splice(it, other, it2); */
    /* display(number); */
    /* display(other); */

    // 5.3 将other链表中迭代器范围的元素转移到it之前
    number.splice(it, other, ++other.begin(), --other.end());
    display(number);
    display(other);

}


int main()
{
    test();
    return 0;
}

