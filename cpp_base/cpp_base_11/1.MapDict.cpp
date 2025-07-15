#include <cctype>
#include <iostream>
#include <map>
#include <fstream>
#include <memory>
#include <sstream>
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::ifstream;
using std::cerr;
using std::istringstream;
using std::ofstream;


class Dictionary
{
public:
    void read(const string &filename);
    void store(const string &filename);
    void dealWord(string & word);
    void insert(string &word);
private:
    map<string, int> _dict;
};

void Dictionary::read(const string &filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "open ifs file failed" << endl;
        return;
    }
    /* cout << "tag->>>>" << endl; */
    string line;
    while (getline(ifs, line)) {
        /* cout << line << endl; */
        istringstream iss(line);
        string word;
        while (iss >> word) {
            // 处理单词
            /* cout << word << endl; */
            dealWord(word);
            // 插入单词到map中
            insert(word);
        }
    }
    ifs.close();
}

void Dictionary::store(const string & filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "ofstream open file failed" << endl;
        return ;
    }
    for (map<string, int>::iterator it = _dict.begin(); it != _dict.end(); it++) {
        ofs << it->first << " " << it->second << endl;
    }
    ofs.close();
}

void Dictionary::insert(string &word) {
    if (word == string()) {
        return;
    }
    ++_dict[word];
}

void Dictionary::dealWord(string & word) {
    auto it = word.begin();
    while (it != word.end()) {
        if (!isalpha(*it)) {
            it = word.erase(it);       
        } else {
            ++it;
        }
    }
}

int main()
{
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");
    dict.store("dictmap.dat");
    return 0;
}

