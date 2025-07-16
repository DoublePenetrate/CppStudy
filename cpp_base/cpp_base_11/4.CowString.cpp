#include <iostream>
#include <ostream>
#include <string.h>

using namespace std;

class CowString 
{
    class CharProxy
    {
    public:
        CharProxy(CowString & self, int idx) 
            : _self(self)
              , _idx(idx)
        {}

        char & operator=(char ch);
        friend ostream & operator<<(ostream & os, const CowString::CharProxy & rhs);  

    private:
        CowString & _self;
        int _idx;
    };
public:
    CowString();
    CowString(const char *);
    CowString(const CowString &);
    CowString & operator=(const CowString &);
    ~CowString();

    const char * c_str() const{ return _pstr; }
    size_t size() const{ return strlen(_pstr); }

    int use_count(){ 
        return *(int*)(_pstr - kRefCountLength); 
    }

    CharProxy operator[](size_t idx);

    friend
        ostream & operator<<(ostream & os,const CowString & rhs);

    friend 
        ostream & operator<<(ostream & os, const CowString::CharProxy & rhs); 
private:
    char * malloc(const char * pstr = nullptr)
    {
        if (pstr) {
            return new char[strlen(pstr) + 1 + kRefCountLength]() + kRefCountLength;
        } else {
            return new char[1 + kRefCountLength]() + kRefCountLength;
        }
    }

    void initRetCount() {
        *(int *)(_pstr - kRefCountLength) = 1;
    }

    void increaseRefCount() {
        ++*(int *)(_pstr - kRefCountLength);
    }

    void decreaseRefCount() {
        --*(int *)(_pstr - kRefCountLength);
    }

    void release() {
        decreaseRefCount();
        if (use_count() == 0) {
            delete [] (_pstr - kRefCountLength);
            _pstr = nullptr;
            cout << ">>> delete heap" << endl;
        }
    }

private:
    static const int kRefCountLength = 4;
    char * _pstr; 
};


ostream & operator<<(ostream & os, const CowString & rhs) {
    if (rhs._pstr) {
        os << rhs._pstr;
    } else {
        os << endl;
    }
    return os;
}

CowString::CowString() 
    : _pstr(malloc())
{
    initRetCount();
}

CowString::CowString(const char * pstr) 
    : _pstr(malloc(pstr))
{
    strcpy(_pstr, pstr);
    initRetCount();
}

CowString::CowString(const CowString & rhs) 
    : _pstr(rhs._pstr)
{
    increaseRefCount();
}

CowString::~CowString() {
    release();
}

CowString & CowString::operator=(const CowString & rhs) {
    if (this != &rhs) {     // 判断自赋值情况
        release();          // 回收堆空间
        _pstr = rhs._pstr;  // 浅拷贝
        increaseRefCount(); // 引用计数+1
    }
    return *this;
}

/* char & CowString::operator[](size_t idx) { */
/* if (idx < size()) { */
/*     if (use_count() > 1) { */
/*         // 1.原本空间引用数 - 1 */
/*         decreaseRefCount(); */
/*         // 2.深拷贝 */
/*         char * temp = malloc(_pstr); */
/*         strcpy(temp, _pstr); */
/*         // 3.改变指向 */
/*         _pstr = temp; */
/*         // 4.初始化新空间的引用计数 */
/*         initRetCount(); */
/*     } */
/*     return _pstr[idx]; */
/* } else { */
/*     cerr << "out of range" << endl; */
/*     static char nullchar = '\0'; */
/*     return nullchar; */
/* } */
/* } */
CowString::CharProxy CowString::operator[](size_t idx) {
    return CharProxy(*this, idx);
}

char & CowString::CharProxy::operator=(char ch) {
    if (_idx < _self.size()) {
        if (_self.use_count() > 1) {
            // 1.原本空间引用计数-1
            _self.decreaseRefCount();
            // 2.深拷贝
            char * temp = _self.malloc(_self._pstr);
            strcpy(temp, _self._pstr);
            // 3.改变指向
            _self._pstr = temp;
            // 4.初始化新空间的引用计数
            _self.initRetCount();
        } 
        // 进行写操作
        _self._pstr[_idx] = ch;
        return _self._pstr[_idx];
    } else {
        cout << "out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}

ostream & operator<<(ostream & os, const CowString::CharProxy & rhs) {
    if (rhs._idx < rhs._self.size()) {
        os << rhs._self._pstr[rhs._idx];
    } else {
        cout << "out of range";
    }
    return os;
}

void test0() {
    CowString str1;
    CowString str2 = str1;
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;

    CowString str3("hello");
    CowString str4 = str3;
    cout << "str3:" << str3 << endl;
    cout << "str4:" << str4 << endl;
    cout << str3.use_count() << endl;
    cout << str4.use_count() << endl;

    cout << endl;
    str2 = str3;
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
    cout << "str3:" << str3 << endl;
    cout << "str4:" << str4 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;
    cout << str3.use_count() << endl;
    cout << str4.use_count() << endl;
}

void test1(){
    CowString str1("hello");
    CowString str2 = str1;
    str2[0] = 'H';
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;

    cout << endl;
    CowString str3 = str1;
    cout << str1[0] << endl;
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
    cout << "str3:" << str3 << endl;
    cout << str1.use_count() << endl;
    cout << str2.use_count() << endl;
    cout << str3.use_count() << endl;
}

int main()
{
    test1();
    return 0;
}

