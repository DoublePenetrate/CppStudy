#include <cctype>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

using std::string;
using std::endl;
using std::set;
using std::map;
using std::vector;
using std::cerr;
using std::cout;


class TextQuery
{
public:
    //读取文件，处理内容，将需要的信息
    void readFile(const string & filename) {
        std::ifstream ifs(filename);
        if (!ifs) {
            cerr << "ifs open file failed" << endl;
            return ;
        }
        // read every line of the target file 
        // and store it in the vector<string> _lines
        string line;
        while (getline(ifs, line)) {
            // raw line has stored the content of a line in aim file
            _lines.push_back(line);
            // deal with the raw line 
            dealLine(line);
            std::istringstream iss(line);
            string word;
            while (iss >> word) {
                _dict[word]++;
                _wordNumbers[word].insert(_lines.size() - 1);
            }
        }
        ifs.close();
    }
    
    // 对一行字符串中的字符进行处理
    // 非字符->' ', 大写字母字符->小写字母字符
    void dealLine(string & line) {
        for (auto & ch : line) {
            if (!isalpha(ch)) {
                ch = ' ';
            } else if (isupper(ch)) {
                ch = tolower(ch);
            }
        }
    }


    //查找单词
    void query(const string & word) {
        cout << "------------------------" << endl;
        if (_dict[word]) {
            print_dict(word);
            print_lines(word);
        } else {
            print_dict(word);    
        }
        cout << "------------------------" << endl;
    }

    // 输出行号和行信息
    void print_lines(const string & word) {
        set<int> lines = _wordNumbers[word];
        set<int>::iterator it = lines.begin();
        for (; it != lines.end(); it++) {
            cout << "(line" << (*it + 1) << ") ";
            cout << _lines[*it] << endl;
        }
    }

    // 输出词频
    void print_dict(const string & word) {
        cout << word << " occurs " << _dict[word] << " times." << endl;
    }

    // 处理单词
    /* void dealWord(string & word) { */
    /*     auto it = word.begin(); */
    /*     while (it != word.end()){ */
    /*         if (!isalpha(*it)) { */
    /*             it = word.erase(it); */
    /*         } else { */
    /*             it++; */
    /*         } */
    /*     } */
    /* } */
private:
    //把每一行的原始信息存储下来
    vector<string> _lines;
    //单词和行号
    map<string, set<int> > _wordNumbers;
    //单词和词频
    map<string, int> _dict;
};

int main()
{
    string queryWord("ahiezer");
    TextQuery tq;
    tq.readFile("The_Holy_Bible.txt");
    tq.query(queryWord);

    return 0;
}

