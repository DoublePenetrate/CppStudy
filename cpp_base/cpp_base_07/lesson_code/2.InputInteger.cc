#include <ios>
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;


int main()
{
    int num;
    cout << "请输入一个int型数据" << endl;

    while (cin >> num, !cin.eof()) {
        if (cin.bad()) {
            cout << "cin has broken" << endl;
        } else if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "请输入一个int型数据" << endl;
        } else {
            cout << "num = " << num << endl;
            break;
        }
    }
    return 0;
}

