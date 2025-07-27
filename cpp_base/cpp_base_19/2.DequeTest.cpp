#include <iostream>
#include <deque>
using std::endl;
using std::cout;
using std::cin;
using std::deque;

template <typename Container>
void display(const Container & con) {
    for (auto & elem : con) {
        cout << elem << " "; 
    }
    cout << endl;
}

// 在任意位置插入元素
void test1() {
    deque<int> deq({1,2,3});
    // deque(双端队列)没有capacity()函数
    //cout << "deq's size = " << deq.capacity() << endl;
    // 1. 在任意位置插入一个元素
    deque<int>::iterator it = deq.begin();
    deq.insert(it, 3);
    it = deq.begin();
    it += 2;
    display(deq);
    /* cout << "deq's size = " << deq.capacity() << endl; */ 
    cout << "*it : " << *it << endl;

    // 2. 在任意位置插入n个元素
    deq.insert(it, 3, 2);
    display(deq);
    /* cout << "deq's size = " << deq.capacity() << endl; */ 
    cout << "size() : " << deq.size() << endl;
    cout << "*it : " << *it << endl;

    // 3. 在任意位置插入迭代器范围的元素
    deque<int> other = {11, 33, 44, 66};
    /* it = deq.begin(); */
    deq.insert(it, other.begin(), other.end());
    display(deq);
    cout << "size() : " << deq.size() << endl;
    /* cout << "deq's size = " << deq.capacity() << endl; */ 
    cout << "*it : " << *it << endl;

    // 4. 在任意位置插入大括号范围的元素
    /* it = deq.begin(); */
    deq.insert(it, {97, 98, 99});
    display(deq);
    /* cout << "deq's size = " << deq.capacity() << endl; */ 
    cout << "size() : " << deq.size() << endl;
    cout << "*it : " << *it << endl;
}

// deque的erase操作
void test2() {
    deque<int> deq = {1, 3, 5, 5, 5, 5, 9, 7, 5, 5, 6};
    for (auto it = deq.begin(); it != deq.end(); ) {
        if (*it == 5) {
            deq.erase(it);
        } else {
            it++;
        }
    }
    display(deq);
    
    // 删除区间位左闭右开区间
    deq.erase(deq.end() - 2, deq.end());
    display(deq);
}

// 元素的清空
void test3() {
    deque<int> deq = {1, 3, 5, 5, 5, 5, 9, 7, 5, 5, 6};
    cout << "size() = " << deq.size() << endl;
    /* cout << "capacity() = " << deq.capacity() << endl; */

    deq.clear();
    cout << "size() = " << deq.size() << endl;
    /* cout << "capacity() = " << deq.capacity() << endl; */
    
    deq.shrink_to_fit();
    cout << "size() = " << deq.size() << endl;
    /* cout << "capacity() = " << deq.capacity() << endl; */
}

// 其他基本操作
void test4() {
    deque<int> deq = {1, 3, 5, 5, 5, 5, 9, 7, 5, 5, 6};
    deque<int> other = {90, 80, 76, 54, 43};
    // 交换容器中的内容
    deq.swap(other);
    display(deq);
    display(other);

    // 更新元素个数
    deq.resize(3);
    display(deq);
    deq.resize(10);
    display(deq);

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
    deque<Point> deq;
    /* deq.reserve(5); */
    deq.push_back(Point(1, 3));
    cout << "---------------" << endl;
    // emplace_back(Point(1, 3)) 会调用拷贝构造
    // 是因为你手动创建了一个临时对象
    // emplace_back 只是把它“拷贝”到容器里去；
    // 要想避免拷贝，应该直接写 emplace_back(1, 3)
    deq.emplace_back(Point(1, 3));
    deq.emplace_back(2, 4);
}

int main()
{
    test();
    return 0;
}


