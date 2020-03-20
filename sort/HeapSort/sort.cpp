#include<iostream>
#include<vector>
using namespace std;

class HeapSort {
public:
	static void heapSort(vector<int>& arr) {
        //构造大根堆
        heapInsert(arr);
        int size = arr.size();
        while (size > 1) {
            //固定最大值
            swap(arr, 0, size - 1);
            size--;
            //构造大根堆
            heapify(arr, size);
        }
	}

    static void heapInsert(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            int currentIndex = i;
            int fatherIndex = (currentIndex - 1) / 2;
            while (arr[currentIndex] > arr[fatherIndex]) {
                swap(arr, currentIndex, fatherIndex);
                currentIndex = fatherIndex;
                fatherIndex = (currentIndex - 1) / 2;
            }
        }
    }

    static void heapify(vector<int>& arr, int size) {
        int left, index, right;
        index = 0;
        left = index * 2 + 1;
        right = index * 2 + 2;
        while (left < size) {
            int largestIndex;
            if (arr[left] < arr[right] && right < size) {
                largestIndex = right;
            }
            else {
                largestIndex = left;
            }
            if (arr[index] >= arr[largestIndex]) {
                break;
            }
            else {
                swap(arr, largestIndex, index);
                index = largestIndex;
                left = 2 * index + 1;
                right = 2 * index + 2;
            }
        }
    }

    static void swap(vector<int>& arr, int a, int b) {
        int temp;
        temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

};

int main() {
    vector<int> arr;
    arr.push_back(6);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(7);
    arr.push_back(9);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);
    arr.push_back(10);
    arr.push_back(8);
    HeapSort::heapSort(arr);
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << endl;
    }
}