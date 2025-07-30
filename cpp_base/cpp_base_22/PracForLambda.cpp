#include <iostream>
#include <vector>

using namespace std;

void test() {
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

int main()
{
    test();
    return 0;
}

