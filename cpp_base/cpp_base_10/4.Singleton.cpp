#include <iostream>

using std::endl;
using std::cin;
using std::cout;

class Singleton
{
public:
    static Singleton * getInstance() {
        if (_pInstance == nullptr) {
            atexit(destory);
            _pInstance = new Singleton(1, 2);
        }
        return _pInstance;
    }


    void init(int x, int y) {
        _ix = x;
        _iy = y;
    }

    void print() const {
        cout << "(" << _ix 
            << "," << _iy
            << ")" << endl;
    }

    friend class AutoRelease;
private:
    static void destory() {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
            cout << ">> delete heap" << endl;
        }
    }

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
    static Singleton * _pInstance;
};
Singleton * Singleton::_pInstance = Singleton::getInstance();


void test() {
    Singleton::getInstance()->print();
    Singleton::getInstance()->init(4, 5);
    Singleton::getInstance()->print();
}

int main()
{
    test();
    return 0;
}

