#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main() {
    char *str;  // 未初始化的野指针
    cin >> str; // 试图向未分配的内存写入数据
    cout << str;
    return 0;
}
