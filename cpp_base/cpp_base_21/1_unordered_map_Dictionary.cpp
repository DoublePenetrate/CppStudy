#include <cctype>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>

using std::endl;
using std::cin;
using std::cout;
using std::string;
using std::unordered_map;
using std::ifstream;
using std::istringstream;
using std::cerr;
using std::ofstream;

class Dictionary
{
public:
    void read(const string & filename) {
        ifstream ifs(filename);
        if (!ifs) {
            cerr << "open" << filename << "fail" << endl;
            return ;
        }

        string line;
        while (getline(ifs, line)) {
            std::istringstream iss(line);
            string word;
            while (iss >> word) {
                string newWord = dealword(word);
                if (newWord != string()) {
                    ++_dict[newWord];
                }
            }
        }
        ifs.close();
    }

    void store(const string & filename) {
        ofstream ofs(filename);
        if (!ofs) {
            cerr << "open" << filename << "fail" << endl;
            return ;
        }
        unordered_map<string,int>::iterator it = _dict.begin();
        for(; it != _dict.end(); it++) {
            ofs << it->first << "  " << it->second << endl;
        }
         ofs.close();
    }

    string dealword(const string & word) {
        for (size_t idx = 0; idx != word.size(); idx++) {
            if (!isalpha(word[idx])) {
                return string();
            }
        }
        return word;
    }
private:
    unordered_map<string,int> _dict;
};

int main()
{
    Dictionary dict;
    time_t beg = time(NULL);
    dict.read("The_Holy_Bible.txt");
    time_t end = time(NULL);
    cout << "time is: " << (end - beg) << "s" << endl;
    dict.store("Bible.dat");
    return 0;
}

