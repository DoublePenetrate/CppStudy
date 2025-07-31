#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void test() {
    vector<int> vec({1,3,5,7,9,2,4,6,8,10});
    auto it = remove_if(vec.begin(), vec.end(), bind1st(std::less<int>(), 5));
    vec.erase(it, vec.end());

    for_each(vec.begin(), vec.end(), [](int value){
             cout << value << " ";
             });
    cout << endl;

}

int main()
{
    test();
    return 0;
}

