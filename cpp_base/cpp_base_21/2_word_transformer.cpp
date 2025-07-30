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
    void read_map(const string & filename);
    void transform(const string & filename);
    void display();
private:
    unordered_map<string, string> _map;
};

void Transformer::read_map(const string & filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "open " << filename << " fail" << endl;
        return ;
    }
    // 读取map.txt 并将其中内容存储在map中
    string line;
    while (getline(ifs, line)) {
        string key;
        string value;
        string tem;
        /* for (size_t idx = 0; idx != line.size(); idx++) { */
        /*     if (line[idx] == ' ') { */
                
        /*     } */
        istringstream iss(line);
        iss >> key;
        while (iss >> tem) {
            value = value + " " + tem;
        }
        _map[key] = value;
    }
}

void Transformer::transform(const string & filename) {
    ifstream ifs("file.txt");
    if (!ifs) {
        cerr << "open " << filename << " fail" << endl;
        return ;
    }

    

}

void Transformer::display() {
    for (auto it = _map.begin(); it != _map.end(); it++) {
        cout << it->first << "  " << it->second << endl;
    }
}

void test() {
    Transformer tran;
    tran.read_map("map.txt");
    tran.display();
}


int main()
{
    test();
    return 0;
}

