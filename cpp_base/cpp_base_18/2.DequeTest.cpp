#include <iostream>
#include <deque>

using std::deque;
using std::cout;
using std::cin;
using std::endl;


template <typename T>
void display(deque<T> & deq) {
    // 1. 使用下标进行遍历
    for (size_t i = 0; i != deq.size(); i++) {
        cout << deq[i] << " "; 
    } 
    cout << endl;

    // 2. 使用迭代器尽心遍历
    for (deque<int>::iterator it = deq.begin(); it != deq.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // 3. 使用auto + for 增强for循环
    for (auto & ele : deq) {
        cout << ele << " ";
    }
    cout << endl;
}

void test() {
    // 1.使用无参构造创建deque
    deque<int> deq1;
    display(deq1);
    // 2.使用count + value初始化deque
    deque<int> deq2(10, 2);
    display(deq2);
    // 3.使用迭代器初始化deque 
    int arr[10] = {1,2,3,4,5,6,7};
    deque<int> deq3(arr, arr + 7);
    display(deq3);
    // 4.使用移动构造或拷贝构造初始化
    // 5.使用大括号初始化deque    
    deque<int> deq4{9,8,7,6,5,4,3,2,1};
    display(deq4);


    cout << "------------------------>" << endl;
    // 在deque尾部进行插入删除
    deq4.push_back(0);
    deq4.push_back(-1);
    display(deq4);
    deq4.pop_back();
    display(deq4);

    cout << "------------------------>" << endl;
    // 在deque头部进行插入与删除
    deq4.push_front(10);
    deq4.push_front(11);
    display(deq4);
    deq4.pop_front();
    display(deq4);
}


int main()
{
    test();
    return 0;
}

