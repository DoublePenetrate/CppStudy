#include <cctype>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::ofstream;
using std::ifstream;
using std::istringstream;
using std::map;

class Dictionary
{
public:
    void read(const string & filename);
    void store(const string & filename);
private:
    string dealWord(const string & word);
    map<string, int> _dict;
};

void Dictionary::read(const string & filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "ifs is not good" << endl;
        return ;
    }

    string line;
    while (getline(ifs, line)) {
        string word;
        istringstream iss(line);
        while (iss >> word) {
            string newWord = dealWord(word);
            if (newWord != string()) {
                _dict[newWord]++;
            }
        }
    }
    ifs.close();
}

void Dictionary::store(const string & filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "ofs is not good" << endl;
        return ;
    }

    auto it = _dict.begin();
    for (; it != _dict.end(); it++) {
        ofs << it->first << "  " << it->second << endl;
    }
    ofs.close();
}

string dealWord(const string & word) {
    for (size_t idx = 0; idx != word.size(); idx++) {
        if (!isalpha(word[idx])) {
            return string();
        }
    }
    return word;
}

void test() {
    Dictionary dict;
    dict.read(string("input.txt"));
    dict.store(string("output2.dat"));
}

int main()
{
    test();
    return 0;
}

