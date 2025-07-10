#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main() {
    vector<int> num1 = {1, 2, 3};
    vector<int> num2 = {2, 3, 4, 5};
    vector<int> num3 = {3, 4, 5, 6, 7};

    vector<vector<int>> Nums1{num1, num2, num3};
    vector<vector<int>> Nums2{{1, 2}, {2, 3}, {3, 4}};

    for (auto ele : Nums1) {
        for (auto u : ele) {
            cout << u << " ";
        }
        cout << endl;
    }

    for (size_t i = 0; i < Nums2.size(); i++) {
        for (size_t j = 0; j < Nums2[i].size(); j++) {
            cout << Nums2[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

