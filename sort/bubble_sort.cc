#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

static void BubbleSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int n = arr.size();
    for (int i = n-1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

TEST(SortTest, BubbleSort) {
    cout << "bubble sort test start\n";
    int max_n = 100;
    int min_val = -20;
    int max_val = 30;
    int test_times = 100000;
    for (int i = 0; i < test_times; i++) {
        vector<int> arr1;
        vector<int> arr2;
        RandomArr(arr1, max_n, min_val, max_val);
        CopyArr(arr1, arr2);
        BubbleSort(arr1);
        std::sort(arr2.begin(), arr2.end());
        if (!IsEqual(arr1, arr2)) {
            Print(arr1);
            Print(arr2);
            ASSERT_TRUE(false);
        }
    }
    cout << "test success\n";
    cout << "bubble sort end\n\n";
}