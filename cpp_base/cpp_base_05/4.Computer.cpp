#include <iostream>
#include <string.h>
using std::endl;
using std::cout;
using std::cin;

class Computer 
{
public:
    static Computer * getInstance() {
        if (nullptr == _pInstance) {
            _pInstance = new Computer("Huawei", 20000);
        }
        return _pInstance;
    }

    static void destory() {
        if (_pInstance != nullptr) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    void init(const char * brand, const double price) {
        if (_brand) {
            delete _brand;
            _brand = nullptr;
        }
        _brand = new char[strlen(brand) + 1]();
        strcpy(_brand, brand);
        _price = price;
    }

    void print() {
        cout << "brand: " << _brand << endl;
        cout << "price: " << _price << endl;
    }

private:
    Computer(const char * brand, double price) 
    : _brand(new char[strlen(brand) + 1]())
    , _price(price)
    {
        strcpy(_brand, brand);
        cout << "Computer(const char *, double)" << endl;
    }

    ~Computer() {
        cout << "~Computer()" << endl;
        if (_brand) {
            delete[] _brand;
            _brand = nullptr; // 安全回收
        }
    }

    Computer(const Computer & rhs) = delete;
    Computer & operator=(const Computer & rhs) = delete;

private:
    char * _brand;
    double _price;
    static Computer * _pInstance;
};
Computer * Computer::_pInstance = nullptr;

void test0() {
    Computer::getInstance();
    Computer::getInstance()->print();
    Computer::getInstance()->init("Apple", 27000);
    Computer::getInstance()->print();
    Computer::destory();
}

int main() {
    test0();
    return 0;
}
