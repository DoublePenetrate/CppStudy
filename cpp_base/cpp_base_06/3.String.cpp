#include <iostream>
#include <cstring>
using std::endl;
using std::cout;
using std::cin;

class String
{
public:
	String();
	String(const char *pstr);
	String(const String &rhs);
	String &operator=(const String &rhs);
	~String();
	void print();
    size_t length() const;
    const char * c_str() const;

private:
	char * _pstr;
};

// String的无参构造
String::String() 
: _pstr(new char[1]())
{
    cout << "String()" << endl;    
}

// 通过c风格字符串构造String
String::String(const char * pstr) 
: _pstr(new char[strlen(pstr) + 1])
{
    cout << "String(const char *)" << endl;
    strcpy(_pstr, pstr);
}

// 拷贝构造函数
String::String(const String & rhs) 
: _pstr(new char[strlen(rhs._pstr) + 1])
{
    cout << "String(const String &)" << endl;
    strcpy(_pstr, rhs._pstr);
}

// 赋值运算符函数
String & String::operator=(const String &rhs) {
    if (this != &rhs) { // 1.自赋值情况判断
        delete [] _pstr; // 2.回收左操作数的数据成员原本申请的堆空间
        _pstr = new char[strlen(rhs._pstr) + 1](); // 3.深拷贝,以及其他的数据成员的赋值
        strcpy(_pstr, rhs._pstr);
    }
    cout << "String & operator=(const String &rhs)" << endl;
    return *this; // 4.返回本对象
}

// String析构函数
String::~String() {
    if (_pstr != nullptr) {
        delete [] _pstr;
        _pstr = nullptr;
    }    
    cout << "~String()" << endl;
}

// 打印函数
void String::print() {
    for (int i = 0; i < strlen(this->_pstr); i++) {
        printf("%c", this->_pstr[i]);
    }
    printf("\n");
}

// 返回String对象的长度
size_t String::length() const {
    return strlen(this->_pstr);
}

const char * String::c_str() const {
    return this->_pstr;
}


int main()
{
	String str1;
	str1.print();

	String str2 = "Hello,world";
	String str3("wangdao");

	str2.print();
	str3.print();

	String str4 = str3;
	str4.print();

	str4 = str2;
	str4.print();

	return 0;
}
