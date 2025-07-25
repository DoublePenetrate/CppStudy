#include <iostream>
#include <list>

using std::list;
using std::cout;
using std::cin;
using std::endl;


template <typename T>
void display(list<T> & li) {
    // 1. 使用下标进行遍历
    /* for (size_t i = 0; i != list.size(); i++) { */
    /*     cout << list[i] << " "; */ 
    /* } */ 
    /* cout << endl; */

    // 2. 使用迭代器尽心遍历
    for (list<int>::iterator it = li.begin(); it != li.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // 3. 使用auto + for 增强for循环
    for (auto & ele : li) {
        cout << ele << " ";
    }
    cout << endl;
}

void test() {
    // 1.使用无参构造创建list
    list<int> list1;
    display(list1);
    // 2.使用count + value初始化list
    list<int> list2(10, 2);
    display(list2);
    // 3.使用迭代器初始化list 
    int arr[10] = {1,2,3,4,5,6,7};
    list<int> list3(arr, arr + 7);
    display(list3);
    // 4.使用移动构造或拷贝构造初始化
    // 5.使用大括号初始化list    
    list<int> list4{9,8,7,6,5,4,3,2,1};
    display(list4);
        
    cout << "------------------------>" << endl;
    // 在listue尾部进行插入删除
    list4.push_back(0);
    list4.push_back(-1);
    display(list4);
    list4.pop_back();
    display(list4);

    cout << "------------------------>" << endl;
    // 在listue头部进行插入与删除
    list4.push_front(10);
    list4.push_front(11);
    display(list4);
    list4.pop_front();
    display(list4);
}


int main()
{
    test();
    return 0;
}

