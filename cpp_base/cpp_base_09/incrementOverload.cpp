#include <iostream>

using std::endl;
using std::cin;
using std::cout;

class Complex
{
public:
    Complex() = default;
    Complex(int real, int image) 
    : _real(real)
    , _image(image)
    {
        cout << "Complex(int, int)" << endl;
    }

    ~Complex()
    {
        cout << "~Complex()" << endl;
    }
    
    Complex(const Complex & rhs)
    : _real(rhs._real)
    , _image(rhs._image)
    {
        cout << "Complex(const Complex &)" << endl;
    }

    Complex & operator=(const Complex & rhs)
    {
        cout << "operator=(const Complex &)" << endl;
        _real = rhs._real;
        _image = rhs._image;
        return *this;
    }

    void print()
    {
        cout << this->_real << " + " << this->_image << "i" << endl;
    }

    // 后置++
    Complex operator++(int)
    {
        cout << "Complex operator++(int)" << endl;
        Complex tmp(*this);
        this->_real++;
        this->_image++;
        return tmp;
    }

    // 前置++
    Complex & operator++()
    {
        cout << "Complex operator++()" << endl;
        this->_real++;
        this->_image++;
        return *this;
    }

friend Complex operator+(const Complex & lhs, const Complex & rhs);

private:
    int _real;
    int _image;
};

Complex operator+(const Complex & lhs, const Complex & rhs)
{
    return Complex(lhs._real + rhs._real, lhs._image + rhs._image);
}

void test()
{
    Complex cp1(2, 4);
    Complex cp2(3, 6);
    Complex cp3 = cp1 + cp2;
    cp3.print();
    cp3++;
    cp3.print();
    ++cp3;
    cp3.print();

}

int main()
{
    test();
    return 0;
}

