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
    friend class ThirdLayer;
private:
    Data * _pdata;
};

class ThirdLayer 
{
public:
    ThirdLayer(MiddleLayer *pml) 
        : _pml(pml)
    {
        cout << "ThirdLayer()" << endl;
    }

    ~ThirdLayer() {
        cout << "~ThirdLayer()" << endl;
        if (_pml != nullptr) {
            delete _pml;
            _pml = nullptr;
        }
    }

    MiddleLayer & operator->() {
        return *_pml;
    }
    
    // 1.解引用 非一步到位
    /* MiddleLayer & operator*() { */
    /*     return *_pml; */
    /* } */

    // 2.解引用 一步到位
    Data operator*() {
        /* return *(*_pml); */
        /* return *((*_pml)._pdata); */
        return (*_pml).operator*();
    }
private:
    MiddleLayer * _pml;
};

void test() {
    ThirdLayer tl(new MiddleLayer(new Data));
    cout << tl->getData() << endl;
    // 解引用 非一步到位
    /* cout << (*(*tl)).getData() << endl; */
    // 解引用 一步到位
    cout << (*tl).getData() << endl;
}

int main()
{
    test();
    return 0;
}

