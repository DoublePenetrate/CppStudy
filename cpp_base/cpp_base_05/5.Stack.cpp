#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class Stack {
public:
    bool empty();	//判断栈是否为空
	bool full();	//判断栈是否已满
	void push(const int & value); //元素入栈
	void pop();     //元素出栈
	int  top();		//获取栈顶元素
    
    Stack(int size = 4) 
    : _capacity(size)
    , _data(new int[_capacity]())
    , _top(-1)
    {
        cout << "Stack(int)" << endl;
    }

    ~Stack() 
    {
        cout << "~Stack()" << endl;
        if (_data != nullptr) {
            delete[] _data;
            _data = nullptr;
        }
    }
private:
    int _capacity;
    int * _data;
    int _top;
};

// 判断栈是否为空
bool Stack::empty() {
    if (_top == -1) {
        return true;
    } 
    return false;
}

// 判断栈是否已满
bool Stack::full() {
    if ((_top + 1) == _capacity) {
        return true;
    }
    return false;
}

// 元素入栈
void Stack::push(const int & value) {
    if (full()) {
        // 扩容栈
        int * old_stack = _data;
        int old_size = _capacity;
        _capacity = old_size * 2;
        _data = new int[_capacity]();
        for (int i = 0; i < old_size; i++) {
            _data[i] = old_stack[i];
        }
        delete[] old_stack;
    }
    _data[++_top] = value;
} 

// 元素出栈
void Stack::pop() {
    if (empty()) {
        cout << "Stack is empty" << endl;
        return;
    }
    _top--;
}

// 获取栈顶元素
int Stack::top() {
    if (empty()) {
        cout << "The stack is empty" << endl;
        return -1;
    }
    return _data[_top];
}

void test() {
    Stack * st = new Stack();
    cout << st->top() << endl;
    st->pop();
    cout << st->empty() << endl;
    st->push(0);
    st->push(1);
    st->push(2);
    st->push(3);
    cout << st->full() << endl;
    cout << st->top() << endl;
    st->push(4);
    cout << st->top() << endl;
    cout << st->full() << endl;
}

int main() {
    test();
    return 0;
}
