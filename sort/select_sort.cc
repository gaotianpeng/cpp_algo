#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

/*
    arr[0～N-1]范围上，找到最小值所在的位置，然后把最小值交换到0位置。
    arr[1～N-1]范围上，找到最小值所在的位置，然后把最小值交换到1位置。
    arr[2～N-1]范围上，找到最小值所在的位置，然后把最小值交换到2位置。
    …
    arr[N-1～N-1]范围上，找到最小值位置，然后把最小值交换到N-1位置。
*/

static void SelectSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(arr[i], arr[min_index]);
        }
    }
}

static void test(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int n = arr.size();
    for (int i = n - 1; i > 0; --i) {
        int max_idx = i;
        for (int j = 0; j < i; j++) {
            if (arr[max_idx] < arr[j]) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            swap(arr[max_idx], arr[i]);
        }
    }
}

//TEST(SortTest, SelectSort) {
//    cout << "select sort test start\n";
//    int max_n = 100;
//    int min_val = -20;
//    int max_val = 30;
//    int test_times = 100000;
//    for (int i = 0; i < test_times; i++) {
//        vector<int> arr1;
//        vector<int> arr2;
//        RandomArr(arr1, max_n, min_val, max_val);
//        CopyArr(arr1, arr2);
//        SelectSort(arr1);
//        std::sort(arr2.begin(), arr2.end());
//        if (!IsEqual(arr1, arr2)) {
//            Print(arr1);
//            Print(arr2);
//            ASSERT_TRUE(false);
//        }
//    }
//    cout << "test success\n";
//    cout << "select sort end\n\n";
//}