#include <iostream>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;

class Person 
{
public:
    // 构造函数
    Person(const char * name, int age)
    : _name(new char[strlen(name) + 1]())
    , _age(age)
    {
        strcpy(_name, name);
        cout << "Person(const char *, int)" << endl;
    }
    // 析构函数
    ~Person()
    {
        cout << "~Person()" << endl;
        if (_name) {
            delete [] _name;
            _name = nullptr;
        }
    }
    // 拷贝构造函数
    Person(const Person & rhs) 
    : _name(new char[strlen(rhs._name) + 1]())
    , _age(rhs._age)
    {
        cout << "Person(const Person &)" << endl;
    }
    // 赋值运算符函数
    Person & operator=(const Person & rhs) {
        if (this != &rhs) {
            delete [] _name;
            _name = new char[strlen(rhs._name) + 1]();
            strcpy(_name, rhs._name);
            _age = rhs._age;
        }
        return *this;
    }

    void display() {
        cout << _name << " " << _age << endl;
    }

    friend class Employee;
private:
    char * _name;
    int _age;
};

class Employee
: public Person 
{
public:
    // 构造函数
    Employee(const char * name, int age, const char * department, int wage)
    : Person(name, age)
    , _department(new char[strlen(department) + 1]())
    , _wage(wage)
    {
        strcpy(_department, department);
        cout << "Employee(const char *, int)" << endl;
    }
    // 析构函数
    ~Employee() {
        cout << "~Employee()" << endl;
        if (_department) {
            delete [] _department;
            _department = nullptr;
        }
    }
    // 拷贝构造函数
    Employee(const Employee & rhs) 
    : Person(rhs)
    , _department(new char[strlen(rhs._department) + 1]())
    , _wage(rhs._wage)
    {
        strcpy(_department, rhs._department);
        cout << "Employee(const Employee &)" << endl;
    }
    // 赋值运算符函数
    Employee & operator=(const Employee & rhs) {
        if (this != &rhs) {
            Person::operator=(rhs);
            delete [] _department;
            _department = new char[strlen(rhs._department) + 1]();
            strcpy(_department, rhs._department);
            _wage = rhs._wage;
        }
        cout << "Employee& operator=(const Employee &)" << endl;
        return *this;
    }
        
    int get_wage() {
        return _wage;
    }

    void display() {
        cout << _name << " "
            << _age << " "
            << _department << " "
            << _wage << endl;
    }

private:
    char * _department;
    int _wage;
};

void test() {
    Employee e1("Erenchan", 22, "IT", 30000);
    Employee e2("Haorong", 23, "IT", 13000);

    e1.display();
    e2.display();

    cout << (e1.get_wage() + e2.get_wage()) / 2 << endl;

}

int main()
{
    test();
    return 0;
}

