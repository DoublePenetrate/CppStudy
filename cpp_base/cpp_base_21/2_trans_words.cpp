#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

using std::string;
using std::endl;
using std::cin;
using std::cout;
using std::unordered_map;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostringstream;
using std::cerr;

class Transformer
{
public:
    void build_map(const string & filename);
    void trans_words(const string & filename);
    void display();
private:
    unordered_map<string, string> _map;
};

void Transformer::build_map(const string & filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "open " << filename << " fail" << endl;
        return ;
    }
    // 读取map.txt 并将其中内容存储在map中
    string key;
    string value;
    while (ifs >> key, getline(ifs, value)) {
        if (value.size() > 1) {
            _map[key] = value.substr(1);
        }
    }
    ifs.close();
}

void Transformer::trans_words(const string & filename) {
    ifstream ifs("file.txt");
    if (!ifs) {
        cerr << "open " << filename << " fail" << endl;
        return ;
    }
    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            auto it = _map.find(word);
            if (it == _map.end()) {
                // 在map中没找到目标
                cout << word;
            } else {
                // 在map中找到目标
                cout << it->second;
            }
            cout << " ";
        }
        cout << endl;
    }
    ifs.close();
}

void Transformer::display() {
    for (auto it = _map.begin(); it != _map.end(); it++) {
        cout << it->first << "  " << it->second << endl;
    }
}

void test() {
    Transformer tran;
    tran.build_map("map.txt");
    tran.trans_words("file.txt");
}


int main()
{
    test();
    return 0;
}

