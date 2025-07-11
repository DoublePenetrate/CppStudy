#include <fstream>
#include <iostream>
using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::cin;

void test01() {
    ifstream ifs;
    ifs.open("test");

    string line;
    while (getline(ifs, line)) {
        cout << line << endl;
    }
}

int main()
{
    test01();
    return 0;
}

