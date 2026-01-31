#include <iostream>
#include <vector>
#include <algorithm>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

/*
    for test
*/
namespace {

static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Random::nextDouble() * (max_n + 1));
	for (int i = 0; i < len; i++) {
		int val = (int)(Random::nextDouble() * (max_val - min_val + 1)) + min_val;
		out.emplace_back(val);
	}
}

} // namespace

static void Heapify(std::vector<int>& arr, int index, int heap_size) {
    int left = index * 2 + 1;
    while (left < heap_size) {
        int largest = left + 1 < heap_size && arr[left] < arr[left + 1] ? left + 1 : left;
        largest = arr[index] < arr[largest] ? largest : index;
        if (largest == index) {
            break;
        }

        ArrayUtils::swap(arr, index, largest);
        index = largest;
        left = index * 2 + 1;
    }
}

static void HeapInsert(std::vector<int>& arr, int index) {
    while (arr[index] > arr[(index - 1) / 2]) {
        ArrayUtils::swap(arr, index, (index - 1)/2);
        index = (index - 1) / 2;
    }
}


static void HeapSort(std::vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int heap_size = arr.size();
    for (int i = 0; i < heap_size; ++i) {
        HeapInsert(arr, i);
    }

    while (heap_size > 0) {
        Heapify(arr, 0, heap_size);
        ArrayUtils::swap(arr, 0, --heap_size);
    }
}

static void HeapSort2(std::vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int heap_size = arr.size();
    for (int i = heap_size - 1; i >= 0; --i) {
        Heapify(arr, i, heap_size);
    }

    ArrayUtils::swap(arr, 0, --heap_size);
    while (heap_size > 0) {
        Heapify(arr, 0, heap_size);
        ArrayUtils::swap(arr, 0, --heap_size);
    }
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        vector<int> arr1, arr2, arr3;
        RandomArr(arr1, max_n, min, max);
        ArrayUtils::copyArray(arr1, arr2);
        ArrayUtils::copyArray(arr1, arr3);
        HeapSort(arr1);
        std::sort(arr2.begin(), arr2.end());
        HeapSort2(arr3);
        if (!ArrayUtils::isEqual(arr1, arr2)) {
            ArrayUtils::printArray(arr1);
            ArrayUtils::printArray(arr2);
            cout << "test failed" << endl;
            break;
        }
        if (!ArrayUtils::isEqual(arr2, arr3)) {
            ArrayUtils::printArray(arr2);
            ArrayUtils::printArray(arr3);
            cout << "test failed" << endl;
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}