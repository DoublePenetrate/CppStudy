#include <iostream>
#include <string.h>
using std::endl;
using std::cout;

class Student {
    public:
        Student(int id, double height, const char * name, double score)
        : _id(id)
        , _height(height)
        , _score(score)
        {
            strcpy(_name, name);
        }
        /*~Student() {
            if (_name) {
                delete [] _name;
                _name = nullptr;
            }
            cout << "~Student()" << endl;
        }*/
        void print() {
            cout<< _id << " "
                << _name << " " 
                << _height << " "
                << _score <<endl;
        }
    private:
        double _height;
        char _name[20];
        int _id;
        double _score;
};

int main(void) {
    Student st_01(510703, 177.8, "Chen Chienkang", 95.5);
    st_01.print();
    return 0;
}
