#include <iostream>
#include <vector>
using std::endl;
using std::cout;
using std::cin;
using std::vector;

template <typename Container>
void display(const Container & con) {
    for (auto & elem : con) {
        cout << elem << " "; 
    }
    cout << endl;
}

// 在任意位置插入元素
void test1() {
    vector<int> vec({1,2,3});
    cout << "vec's size = " << vec.capacity() << endl;
    // 1. 在任意位置插入一个元素
    vector<int>::iterator it = vec.begin();
    vec.insert(it, 3);
    it = vec.begin();
    it += 2;
    display(vec);
    cout << "vec's size = " << vec.capacity() << endl; 
    cout << "*it : " << *it << endl;

    // 2. 在任意位置插入n个元素
    vec.insert(it, 3, 2);
    display(vec);
    cout << "vec's size = " << vec.capacity() << endl; 
    cout << "*it : " << *it << endl;

    // 3. 在任意位置插入迭代器范围的元素
    vector<int> other = {11, 33, 44, 66};
    it = vec.begin();
    vec.insert(it, other.begin(), other.end());
    display(vec);
    cout << "vec's size = " << vec.capacity() << endl; 
    cout << "*it : " << *it << endl;

    // 4. 在任意位置插入大括号范围的元素
    it = vec.begin();
    vec.insert(it, {97, 98, 99});
    display(vec);
    cout << "vec's size = " << vec.capacity() << endl; 
    cout << "*it : " << *it << endl;
}

// vector的erase操作
void test2() {
    vector<int> vec = {1, 3, 5, 5, 5, 5, 9, 7, 5, 5, 6};
    for (auto it = vec.begin(); it != vec.end(); ) {
        if (*it == 5) {
            vec.erase(it);
        } else {
            it++;
        }
    }
    display(vec);
    
    // 删除区间位左闭右开区间
    vec.erase(vec.end() - 2, vec.end());
    display(vec);
}

// 元素的清空
void test3() {
    vector<int> vec = {1, 3, 5, 5, 5, 5, 9, 7, 5, 5, 6};
    cout << "size() = " << vec.size() << endl;
    cout << "capacity() = " << vec.capacity() << endl;

    vec.clear();
    cout << "size() = " << vec.size() << endl;
    cout << "capacity() = " << vec.capacity() << endl;
    
    vec.shrink_to_fit();
    cout << "size() = " << vec.size() << endl;
    cout << "capacity() = " << vec.capacity() << endl;
}

// 其他基本操作
void test4() {
    vector<int> vec = {1, 3, 5, 5, 5, 5, 9, 7, 5, 5, 6};
    vector<int> other = {90, 80, 76, 54, 43};
    // 交换容器中的内容
    vec.swap(other);
    display(vec);
    display(other);

    // 更新元素个数
    vec.resize(3);
    display(vec);
    vec.resize(10);
    display(vec);

    // 获取容器的第一个和最后一个元素(三种序列式容器都支持)
    // 返回的是对应元素的引用
    cout <<  "other.front() = " << &other.front() << endl;
    cout << "other.back() = " << &other.back() << endl;
}

class Point 
{
public:
    Point(int x = 0, int y = 0)
    : _ix(x)
    , _iy(y)
    {
        cout << "Point(int, int)" << endl;
    }

    Point(const Point & rhs) 
    : _ix(rhs._ix)
    , _iy(rhs._iy)
    {
        cout << "Point(const Point &)" << endl;
    }

private:
    int _ix;
    int _iy;
};

// emplace_back
void test() {
    vector<Point> vec;
    vec.reserve(5);
    vec.push_back(Point(1, 3));
    cout << "---------------" << endl;
    // emplace_back(Point(1, 3)) 会调用拷贝构造
    // 是因为你手动创建了一个临时对象
    // emplace_back 只是把它“拷贝”到容器里去；
    // 要想避免拷贝，应该直接写 emplace_back(1, 3)
    vec.emplace_back(Point(1, 3));
    vec.emplace_back(2, 4);
}

int main()
{
    test();
    return 0;
}

