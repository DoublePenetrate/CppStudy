#include <iostream>
#include <string.h>
using std::endl;
using std::cout;
using std::cin;

class CharArray {
public:
    CharArray(const char * pstr)
    : _capacity(strlen(pstr) + 1)
    , _data(new char[_capacity]())
    {
        strcpy(_data, pstr);
    }

    ~CharArray()
    {
        if (_data){
            delete [] _data;
            _data = nullptr;
        }
    }

    char & operator[](size_t idx)
    {
        cout << "char & operator[]()" << endl;
        if (idx < _capacity - 1){
            return _data[idx];
        } else {
            cout << "out of range" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }

    const char & operator[](size_t idx) const {
        cout << "const char & operator[]() const" << endl;
        if (idx < _capacity - 1) {
            return _data[idx];
            /* _data[0] = 'C'; */
        } else {
            cout << "out of range" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }
    
    void print() const {
        cout << _data << endl;
    }

private:
    size_t _capacity;
    char * _data;
};

void test() 
{
    CharArray ca("hello, world");
    cout << ca[2] << endl;
    ca[2] = 'L';
    ca.print(); 

    const CharArray ca1("Erenchan");
    ca1.print();
    cout << ca1[2] << endl;
    /* ca1[4] = 'N'; */
    cout << ca1[4] << endl;
}

int main()
{
    test();
    return 0;
}

