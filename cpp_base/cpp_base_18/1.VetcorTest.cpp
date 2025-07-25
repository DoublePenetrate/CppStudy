#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;


template <typename T>
void display(vector<T> & vec) {
    // 1. 使用下标进行遍历
    for (size_t i = 0; i != vec.size(); i++) {
        cout << vec[i] << " "; 
    } 
    cout << endl;

    // 2. 使用迭代器尽心遍历
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // 3. 使用auto + for 增强for循环
    for (auto & ele : vec) {
        cout << ele << " ";
    }
    cout << endl;
}

void test() {
    // 1.使用无参构造创建vector
    vector<int> vec1;
    display(vec1);
    // 2.使用count + value初始化vector
    vector<int> vec2(10, 2);
    display(vec2);
    // 3.使用迭代器初始化vector 
    int arr[10] = {1,2,3,4,5,6,7};
    vector<int> vec3(arr, arr + 7);
    display(vec3);
    // 4.使用移动构造或拷贝构造初始化
    // 5.使用大括号初始化vector    
    vector<int> vec4{9,8,7,6,5,4,3,2,1};
    display(vec4);
        
}


int main()
{
    test();
    return 0;
}

