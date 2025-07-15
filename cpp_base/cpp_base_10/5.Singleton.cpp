#include <iostream>
#include <pthread.h>

using std::endl;
using std::cin;
using std::cout;

class Singleton
{
public:
    static Singleton * getInstance() {
        pthread_once(&_once, init_r);
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

private:
    static void destory() {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
            cout << ">> delete heap" << endl;
        }
    }

    static void init_r() {
        _pInstance = new Singleton(1, 2);
        atexit(destory);
    }

    Singleton() = default;
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
    static pthread_once_t _once;
};
Singleton * Singleton::_pInstance = nullptr;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;


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

