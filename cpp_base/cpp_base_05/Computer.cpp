#include <iostream>
#include <string.h>
using std::endl;
using std::cout;

// 实现只能创建堆对象,不能创建栈对象的Computer类
// 包含品牌和价格信息；
class Computer {
    // 只能创建堆对象,不能创建栈对象 表示私有化析构函数
public:
    // 构造函数
    Computer(const char * brand, int price) 
    : _brand(new char[strlen(brand) + 1]())
    , _price(price)
    {
        strcpy(_brand, brand);
    }

    //拷贝构造函数
    //赋值运算符函数
    void * operator new(size_t sz) {
        void * ret = malloc(sz);
        return ret;
    }

    void operator delete(void * p) {
        free(p);
    }

private:
    // 析构函数
    ~Computer() 
    {
        delete [] _brand;
    }

    char * _brand;
    int _price;
};

int main() {
    Computer cp1("Apple", 20000);
    Computer * cp2 = new Computer("Huawei", 19000);
}
