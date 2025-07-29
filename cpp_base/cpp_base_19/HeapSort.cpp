#include <iostream>
#include <vector>

using std::endl;
using std::cout;
using std::vector;

class HeadSorter
{
public:
    HeadSorter(int * arr, size_t size)
    : _vec(vector<int>(arr, arr + size))
    {}

    ~HeadSorter() {

    }

    void sort() {
        int n = _vec.size();
        buildHeap(n);

        for (int i = n - 1; i > 0; i--) {
            std::swap(_vec[i], _vec[0]);
            heapify(i, 0);
        }
    }

    void display() {
        int n = _vec.size();
        for (auto & elem : _vec) {
            cout << elem << " "; 
        }
        cout << endl;
    }

private:
    vector<int> _vec;  
    // 建立大根堆
    void heapify(int n, int i) {
        int largest = i;
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        if (left < n && _vec[left] > _vec[largest]) largest = left;
        if (right < n && _vec[right] > _vec[largest]) largest = right;

        if (largest != i) {
            std::swap(_vec[i], _vec[largest]);
            heapify(n, largest);
        }
    }

    void buildHeap(int n) {
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(n, i);
        }
    }
    
};

void test() {
    int arr[10] = {1,3,5,7,9,2,4,6,8,10};
    HeadSorter hs(arr, 10);
    hs.sort();
    hs.display();
}

int main()
{
    test();
    return 0;
}

