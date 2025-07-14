#include <iostream>
using std::endl;
using std::cin;
using std::cout;


class FFF
{
public:
    void print(int x){
        cout << "FFF::print:" << x << endl;
    }

    void display(int x){
        cout << "FFF::display:" << x << endl;
    }
};

typedef void (FFF::*MemberFunc)(int);

void test() {
    void (FFF::*p)(int) = &FFF::print;
    FFF fff;
    (fff.*p)(4);
    
    MemberFunc mf = &FFF::display;
    FFF ff;
    (ff.*mf)(4); 

    FFF * fp = new FFF;
    (fp->*mf)(4);
}

int main()
{
    test();
    return 0;
}

