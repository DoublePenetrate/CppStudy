#include <iostream>
#include <string.h>
#include <vector>
using std::endl;
using std::cout;
using std::cin;
using std::vector;

class String
{
public:
    String()
        : _pstr(new char[1]())
    {
        cout << "String()" << endl;
    }

    String(const char *pstr)
        : _pstr(new char[strlen(pstr)+1]())
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
    }

    String(const String & rhs) 
        : _pstr(new char[strlen(rhs._pstr)+1]())
    {
        cout << "String(const String &)" << endl;
        strcpy(_pstr, rhs._pstr);
    }

    ~String()
    {
        cout << "~String()" << endl;
        if (_pstr) {
            delete [] _pstr;
            _pstr = nullptr;
        }
    }

    String &operator=(const String &rhs) {
        cout << "String &operator=(const String &)" << endl;
        if (&rhs != this) {
            delete [] _pstr;
            _pstr = nullptr;
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        return *this;
    }

    String &operator=(const char * pstr) {
        cout << "String &operator=(const const char *)" << endl;
        delete [] _pstr;
        _pstr = nullptr;
        _pstr = new char[strlen(pstr) + 1]();
        strcpy(_pstr, pstr);
        return *this;
    }

    String &operator+=(const String & rhs) {
        cout << "String &operator+=(const String &)" << endl;
        char * temp = new char[strlen(_pstr) + strlen(rhs._pstr) + 1]();
        strcpy(temp, _pstr);
        strcat(temp, rhs._pstr);
        delete [] _pstr;
        _pstr = temp;
        return *this;
    }
    String &operator+=(const char * pstr) {
        cout << "String &operator+=(const char *)" << endl;
        String temp(pstr);
        (*this) += temp;
        return *this;
    }

    char &operator[](std::size_t index) {
        cout << "char &operator[](std::size_t index)" << endl;
        if (index < strlen(_pstr)) {
            return _pstr[index];
        } else {
            static char nullchar = '\0';
            return nullchar;
        }
    }
    const char &operator[](std::size_t index) const {
        cout << "const char &operator[](std::size_t index) const" << endl;
        if (index < strlen(_pstr)) {
            return _pstr[index];
        } else {
            static char nullchar = '\0';
            return nullchar;
        }
    }

    std::size_t size() const {
        return strlen(_pstr);
    }
    const char* c_str() const {
        return _pstr;
    }

    friend bool operator==(const String & lhs, const String & rhs);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char * _pstr;
};

bool operator==(const String & lhs, const String & rhs) {
    return !strcmp(lhs._pstr, rhs._pstr);
}

bool operator!=(const String & lhs, const String & rhs) {
    return strcmp(lhs._pstr, rhs._pstr);
}

bool operator<(const String & lhs, const String & rhs) {
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}
bool operator>(const String & lhs, const String & rhs) {
    return strcmp(lhs._pstr, rhs._pstr) > 0;
}
bool operator<=(const String & lhs, const String & rhs) {
    return strcmp(lhs._pstr, rhs._pstr) <= 0;
}
bool operator>=(const String & lhs, const String & rhs) {
    return strcmp(lhs._pstr, rhs._pstr) >= 0;
}

std::ostream &operator<<(std::ostream &os, const String &rhs) 
{
    if (rhs._pstr) {
        os << rhs._pstr;
    }
    return os;
}

std::istream &operator>>(std::istream &is, String &rhs)
{
    if (rhs._pstr) {
        delete [] rhs._pstr;
        rhs._pstr = nullptr;
    }

    char ch;
    vector<char> buffer;
    while ((ch = is.get()) != '\n') {
        buffer.push_back(ch);
    }

    rhs._pstr = new char[buffer.size() + 1]();
    strncpy(rhs._pstr, &buffer[0], buffer.size());

    return is;
}

String operator+(const String & lhs, const String & rhs) {
    cout << "String operator+(const String &, const String &)" << endl;
    char * tmp = new char[lhs.size() + rhs.size() + 1]();
    strcpy(tmp, lhs.c_str());
    strcat(tmp, rhs.c_str());
    return String(tmp);
}

String operator+(const String & lhs, const char * pstr) {
    cout << "String operator+(const String &, const char *)" << endl;
    String rhs(pstr);
    return lhs + rhs;
}

String operator+(const char * pstr, const String & rhs) {
    cout << "String operator+(const char *, const String &)" << endl;
    String lhs(pstr);
    return lhs + rhs;
}

void test() {
    String s1;
    cin >> s1;
    cout << "s1 = " << s1 << endl;
    cout << endl;

    cout << endl << endl;
    String s2 = "hello";
    cout << "s2 = " << s2 << endl;
    cout << endl;
    s2 = "world";
    cout << "s2 = " << s2 << endl;
    cout << endl;
    s2 = s2;
    cout << "s2 = " << s2 << endl;
    cout << endl;
    String s3 = "wuhan";
    String s4 = ", world";
    s3 += s4;
    cout << "s3 = " << s3 << endl;
    s3 += " welcome to string word";
    cout << "s3 = " << s3 << endl;
}

int main() {
    test();
    return 0;
}
