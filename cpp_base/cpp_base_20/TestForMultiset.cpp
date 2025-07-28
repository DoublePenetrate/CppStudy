#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>


using std::endl;
using std::cin;
using std::cout;
using std::multiset;
using std::pair;
using std::lower_bound;
using std::upper_bound;


template <typename Container>
void display(const Container & con) {
    for (auto & elem : con) {
        cout << elem << " ";
    }
    cout << endl;
}

void test1() {
    multiset<int> number = {3, 3, 11, 98, 5, 26};
    display(number);

    // 1.查找目标元素
    size_t num = number.count(3);
    cout << "num = " << num << endl;
    multiset<int>::iterator it = number.find(4);
    if (it != number.end()) {
        cout << "查找成功 " << *it << endl;
    } else {
        cout << "查找失败 " << endl;
    }
    cout << "------------------" << endl;

    // 2.插入元素
    /* pair<multiset<int>::iterator, bool> it2 = number.insert(1); */ // error
    // multiset插入一个元素的返回类型为迭代器
    multiset<int>::iterator it2 = number.insert(1);
    /* cout << "插入元素: *it = " << *it2.first << " bool = " << it2.second << endl; */
    cout << "插入元素: *it = " << *it2 << endl;
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
    /* int tem = number[3]; */  // error 说明multiset不支持取下标操作
    auto it4 = number.find(3);
    /* *it4 = 6; */ // error 说明不能对迭代器iterator 进行解引用修改

}

void test() {
    multiset<int> number({1, 2, 2, 3, 3, 4, 5, 9, 3, 20, 15, 3}); 
    display(number);
    multiset<int>::iterator it1 = number.lower_bound(3);
    multiset<int>::iterator it2 = number.upper_bound(3);
    cout << "lower_bound = " << *it1 << endl;
    cout << "upper_bound = " << *it2 << endl;
    
    for (; it1 != it2; it1++) {
        cout << *it1 << " ";
    }
    cout << endl;
    cout << "--------------------" << endl;

    pair<multiset<int>::iterator, multiset<int>::iterator> ret
        = number.equal_range(3);
    while (ret.first != ret.second) {
        cout << *ret.first << " ";
        ++ret.first;
    }
    cout << endl;
}

int main()
{
    test();
    return 0;
}

