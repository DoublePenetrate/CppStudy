#include <cctype>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::string;
using std::ofstream;
using std::ifstream;
using std::istringstream;
using std::ostringstream;

struct Record
{
    Record(const string & word, int frequency)
    : _word(word)
    , _frequency(frequency)
    {

    }
    string _word;
    int _frequency;
};

class Dictionary
{
public:
    //读文件，然后将结果存放在vector
    void read(const string & filename) {
        ifstream ifs(filename);
        if (!ifs) {
            cerr << "ifstream is not good" << endl;
            return ;
        }

        string line;
        //对文件中的内容一行行进行处理
        while (getline(ifs, line)) {
            string word;
            istringstream iss(line);
            while (iss >> word) {
                //查看word是不是合格的单词，如果不是就进行处理
                string newWord = dealWord(word);
                //将合格的单词（处理之后的单词放在vector存起来）
                insert(word);
            }
        }
        //将vector中的所有Record进行排序
        sort(_dict.begin(), _dict.end());

        ifs.close();
    }
    // 读vector将其中内容存放到文件中
    void store(const string & filename) {
        ofstream ofs(filename);
        if (!ofs) {
            cerr << "ofstream is not good" << endl;
            return ;
        }
        // 遍历vector, 将其中内容写到文件中
        for (size_t idx = 0; idx != _dict.size(); idx++) {
            ofs << _dict[idx]._word << "  "
                << _dict[idx]._frequency << endl;
        }
        ofs.close();
    }


private:
    string dealWord(const string & word) {
        for (size_t idx = 0; idx != word.size(); idx++) {
            if (!isalpha(word[idx])) {
                return string();
            }
        }
        return word;
    }

    void insert(const string & word) {
        if (word == string())
        {
            return ;
        }
        // 将word存放到vector中
        size_t idx = 0;
        for (; idx < _dict.size(); idx++) {
            if (_dict[idx]._word == word) {
                _dict[idx]._frequency++;
                return ;
            }
        }
        // 说明单词第一次出现
        _dict.push_back(Record(word, 1));
    }
    
private:
    vector<Record> _dict;
};

bool operator<(const Record & lhs, const Record & rhs) {
    return lhs._frequency > rhs._frequency;
}


void test() {
    Dictionary dic;
    dic.read(string("input.txt"));
    dic.store("output.dat");
}

int main()
{
    test();
    return 0;
}

