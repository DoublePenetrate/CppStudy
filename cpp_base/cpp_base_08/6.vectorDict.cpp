#include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostringstream;

struct Record
{
    Record(string word, int frequency = 1) 
    : _word(word)
    , _frequency(frequency)
    {}

    ~Record() 
    {}
	string _word;
	int _frequency;
};

bool operator<(const Record & lhs, const Record & rhs) 
{
    return lhs._word < rhs._word;
}

class Dictionary
{
public:
	// 构造函数
    Dictionary(int num)
    {
        _dict.reserve(num);
        cout << "Dictionary(int)" << endl;
    }

    ~Dictionary() 
    {
        cout << "~Dictionary()" << endl;
    }

    void read(const std::string &filename) {
        ifstream ifs(filename);
        if (!ifs) {
            cerr << "ifs open file failed" << endl;
            return;
        }
        string line;
        while (getline(ifs, line)) {
            istringstream iss(line); //默认为out
            string word;
            while (iss >> word) {
                string newWord = dealWord(word);
                insert(newWord);
            }
        }
        ifs.close();
        sort(_dict.begin(), _dict.end());
    }

    string dealWord(const string & word) 
    {
        // 处理单词
        for (size_t idx = 0; idx < word.size(); idx++) {
            if (!isalpha(word[idx]))
            {
                // 当出现非字母字符时 进行处理
                return string();
            }
        }
        return word;
    }

    void insert(const string & word)
    {
        if (word == string()) {
            return;
        }
        for (size_t idx = 0; idx < _dict.size(); idx++) 
        {
            if (word == _dict[idx]._word) {
                _dict[idx]._frequency++;
                return;
            }
        }
        // 插入新的record
        _dict.push_back(Record(word));
    }

    void store(const std::string &filename) 
    {
        ofstream ofs = ofstream(filename);
        if (!ofs) {
            cerr << "open ofs file failed" << endl;
        }
        for (size_t idx = 0; idx < _dict.size(); idx++) {
            string line;
            line.append(_dict[idx]._word);
            line.append(" ");
            line.append(std::to_string(_dict[idx]._frequency));
            ofs << line << endl;
        }
        ofs.close();
    }
private:
    vector<Record> _dict;
};

void test() {
    Dictionary dict(10000);
    dict.read("The_Holy_Bible.txt");
    dict.store("wordCount.txt");
}

int main()
{
    test();
    return 0;
}

