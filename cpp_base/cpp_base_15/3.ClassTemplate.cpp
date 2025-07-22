#include <iostream>

using std::endl;
using std::cin;
using std::cout;

template <class T = int, int kCapacity = 10>
class Stack 
{
public:
    Stack() 
    : _top(-1)
    , _data(new T[kCapacity])
    {
        cout << "Stack()" << endl;
    }

    ~Stack() {
        if (_data) {
            delete [] _data;
            _data = nullptr;
        }
        cout << "~Stack()" << endl;
    }

    bool full() const {
        if (_top == kCapacity - 1) {
            return true;
        } 
        return false;
    }

    bool empty() const {
        return _top == -1;
    }

    void push(const T & t) {
        if (!full()) {
            _data[++_top] = t;
        } else {
            throw "full";
        }
    }

    void pop() {
        if (!empty()) {
            _top--;
        } else {
            throw "empty";
        }
    }

    T top() {
        if (!empty()) {
            return _data[_top];
        } else {
            throw "empty";
        }
    }

private:
    int _top;
    T * _data;
};

void test() {
    Stack st;
    st.push(1);
    st.push(2);
    cout << st.empty() << endl;
    cout << st.full() << endl;
    cout << st.top() << endl;
    st.pop();
    cout << st.top() << endl;

    cout << endl;

    Stack<double> ss;
    ss.push(1.2);
    ss.push(4.55);
    ss.push(8.9);
    cout << ss.top() << endl;
    ss.pop();
    cout << ss.top() << endl;
}

int main()
{
    test();
    return 0;
}

