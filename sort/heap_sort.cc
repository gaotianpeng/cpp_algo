#include <iostream>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

static void heapify(vector<int>& arr, int index, int heap_size) {
    int left = 2 * index + 1;
    while (left < heap_size) {
        int largest = left + 1 < heap_size && arr[left + 1] > arr[left] ? left + 1 : left;
        largest = arr[largest] > arr[index] ? largest :index;
        if (largest == index) {
            break;
        }

        swap(arr[largest], arr[index]);
        index = largest;
        left = index * 2 + 1;
    }
}

static void HeapSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int n = arr.size();
    for (int i = n - 1; i >= 0; --i) {
        heapify(arr, i, n);
    }

    int heap_size = n;
    swap(arr[0], arr[--heap_size]);
    while (heap_size > 0) {
        heapify(arr, 0, heap_size);
        swap(arr[0], arr[--heap_size]);
    }
}

//TEST(SortTest, HeapSort) {
//    cout << "heap sort test start\n";
//    int max_n = 100;
//    int min_val = -20;
//    int max_val = 30;
//    int test_times = 100000;
//    for (int i = 0; i < test_times; i++) {
//        vector<int> arr1;
//        vector<int> arr2;
//        RandomArr(arr1, max_n, min_val, max_val);
//        CopyArr(arr1, arr2);
//        HeapSort(arr1);
//        std::sort(arr2.begin(), arr2.end());
//        if (!IsEqual(arr1, arr2)) {
//            Print(arr1);
//            Print(arr2);
//            ASSERT_TRUE(false);
//        }
//    }
//    cout << "test success\n";
//    cout << "heap sort end\n\n";
//}