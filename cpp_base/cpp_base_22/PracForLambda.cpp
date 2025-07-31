#include <iostream>
#include <vector>

using namespace std;

// [=]捕获全部变量,全部采用值传递
// mutable表示可以修改lambda表达式中变量的值
// 但不会修改lambda表达式外变量的值
void test1() {
    int a = 10;
    string name = "Erenchan";
    int age = 22;
    
    [=](int grade) mutable{
        age = 23;
        name = "Wanghaorong";
        grade = 130;
        cout << "name = " << name << endl; 
        cout << "age = " << age << endl;
        cout << "grade = " << grade << endl; 
        cout << "a = " << a << endl;
    }(145);

    cout << "name = " << name << endl; 
    cout << "age = " << age << endl;
    cout << "a = " << a << endl;
}

void test2() {
    string name = "Erenchan";
    int age = 22;
    
    [&](int grade) {
        age = 23;
        name = "Wanghaorong";
        grade = 130;
        cout << "name = " << name << endl; 
        cout << "age = " << age << endl;
        cout << "grade = " << grade << endl; 
    }(145);

    cout << "name = " << name << endl; 
    cout << "age = " << age << endl;

}

void test() {
    string name = "Erenchan";
    int age = 22;
    
    [&, age](int grade) {
        /* age = 23; */ // error
        name = "Wanghaorong";
        grade = 130;
        cout << "name = " << name << endl; 
        cout << "age = " << age << endl;
        cout << "grade = " << grade << endl; 
    }(145);

    cout << "name = " << name << endl; 
    cout << "age = " << age << endl;

}

int main()
{
    test();
    return 0;
}

