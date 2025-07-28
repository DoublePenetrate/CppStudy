#include <iostream>
#include <set>
#include <utility>
#include <vector>

using std::endl;
using std::cin;
using std::cout;
using std::set;
using std::pair;

template <typename Container>
void display(const Container & con) {
    for (auto & elem : con) {
        cout << elem << " ";
    }
    cout << endl;
}

void test() {
    set<int> number = {3, 3, 11, 98, 5, 26};
    display(number);

    // 1.查找目标元素
    size_t num = number.count(3);
    cout << "num = " << num << endl;
    set<int>::iterator it = number.find(4);
    if (it != number.end()) {
        cout << "查找成功 " << *it << endl;
    } else {
        cout << "查找失败 " << endl;
    }
    cout << "------------------" << endl;

    // 2.插入元素
    pair<set<int>::iterator, bool> it2 = number.insert(1);
    cout << "插入元素: *it = " << *it2.first << " bool = " << it2.second << endl;
    display(number);
    std::vector<int> vec = {1, 2, 4, 6, 9};
    number.insert(vec.begin(), vec.end());
    display(number);
    number.insert({7, 8, 10});
    display(number);

    // 3.删除元素
    auto it3 = number.find(6);
    number.erase(it3);
    display(number);

    // 4.是否支持下标操作
    /* int tem = number[3]; */  // error 说明set不支持取下标操作
    auto it4 = number.find(3);
    /* *it4 = 6; */ // error 说明不能对迭代器iterator 进行解引用修改

}

int main()
{
    test();
    return 0;
}

