#include <iostream>
#include <vector>

using std::cin;
using std::endl;
using std::cout;
using std::vector;

class QuickSort
{
public:
    QuickSort(int * arr, size_t size)
    : _vec(vector<int>(arr, arr + size))
    {
        cout << "QuickSort执行" << endl;
        quickSort(0, size - 1);
    }

    void display() const {
        for (auto & ele : _vec) {
            cout << ele << " ";
        }
        cout << endl;
    }

private:
    int partition(int left, int right) {
        int pivot = _vec[left];
        while (left < right) {
            while (left < right && _vec[right] >= pivot) right--;
            _vec[left] = _vec[right];
            while (left < right && _vec[left] <= pivot) left++;
            _vec[right] = _vec[left];
        }
        _vec[left] = pivot;
        
        return left;
    }

    void quickSort(int left, int right) {
        if (left < right) {
            int pivotIndex = partition(left, right);
            quickSort(left, pivotIndex - 1);
            quickSort(pivotIndex + 1, right);
        }
    }

private:
    vector<int> _vec;
};

int main()
{
    int arr[9] = {1,3,5,7,9,2,4,6,8};
    QuickSort qs(arr, 9);
    qs.display();
    return 0;
}

