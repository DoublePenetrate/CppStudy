#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Singleton 
{
    class AutoRelease
    {
    public:
        AutoRelease() 
        {}
        ~AutoRelease()
        {
            if (_pinstance) {
                delete _pinstance;
                _pinstance = nullptr;
            }
        }
    };

public:
    static Singleton * getInstance()
    {
        if (_pinstance == nullptr) {
            _pinstance = new Singleton(1, 2);
        }
        return _pinstance;
    }

    void init(int x, int y) {
        _ix = x;
        _iy = y;
    }

    static void destory() {
        if (_pinstance) {
            delete _pinstance;
            _pinstance = nullptr;
            cout << ">> delete heap" << endl;
        }
    }

    void print() const {
        cout << "(" << _ix
            << "," << _iy
            << ")" << endl;
    }

private:
    Singleton(int x, int y)
    : _ix(x)
    , _iy(y)
    {
        cout << "Singleton(int, int)" << endl;
    }

    ~Singleton() {
        cout << "~Singleton()" << endl;
    }

    Singleton(const Singleton & rhs) = delete;
    Singleton & operator=(const Singleton & rhs) = delete;

    int _ix;
    int _iy;
    static Singleton * _pinstance;
    static AutoRelease _ar;
};
Singleton * Singleton::_pinstance = nullptr;
Singleton::AutoRelease Singleton::_ar;

void test() {
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(5, 7);
    Singleton::getInstance()->print();

}

int main()
{
    test();
    return 0;
}

