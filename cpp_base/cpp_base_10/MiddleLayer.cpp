#include <iostream>
using std::endl;
using std::cin;
using std::cout;

class Data
{
public:
    Data(){}
    ~Data(){}
    int getData() {
        return _data;
    }

private:
    int _data = 10;
};

// 创建MiddleLayer对象ml，让ml对象可以使用箭头运算符去调用Data类的成员函数getData()
// MiddleLayer ml(new Data);
// cout << ml->getData() << endl;

class MiddleLayer {
public:
    MiddleLayer(Data * p)
    : _pdata(p)
    {}

    ~MiddleLayer() {
        if (_pdata != nullptr) {
            delete _pdata;
            _pdata = nullptr;
        }
    }

    Data * operator->() {
        return this->_pdata;
    }

    Data operator*() {
        return *(this->_pdata);
    }
private:
    Data * _pdata;
};

void test() {
    MiddleLayer ml(new Data);
    cout << ml->getData() << endl;
    cout << (*ml).getData() << endl;
}

int main()
{
    test();
    return 0;
}

