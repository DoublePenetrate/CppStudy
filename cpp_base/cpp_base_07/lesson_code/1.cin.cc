#include <ios>
#include <iostream>
#include <limits>
#include <string>
using std::string;
using std::endl;
using std::cout;
using std::cin;

void printStreamStatus(std::istream &is) {
    cout << "is's goodbit:" << is.good() << endl;
    cout << "is's badbit:" << is.bad() << endl;
    cout << "is's failbit:" << is.fail() << endl;
    cout << "is's eofbit:" << is.eof() << endl;
}

int main() {
    printStreamStatus(cin);
    int num;
    cin >> num;
    cout << "num = " << num << endl;
    printStreamStatus(cin);
    
    if (!cin.good()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
    }
    string line;
    cin >> line;
    cout << line << endl;

    return 0;
}
