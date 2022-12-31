#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

static std::pair<int, int> netherlandsFlag(vector<int>& arr, int left, int right) {
    if (left > right) {
        return {-1, -1};
    }

    if (left == right) {
        return {left, right};
    }

    int less = left - 1;
    int more = right;
    int index = left;
    while (index < more) {
        if (arr[index] == arr[right]) {
            index++;
        } else if (arr[index] < arr[right]) {
            swap(arr[index++], arr[++less]);
        } else {
            swap(arr[index], arr[--more]);
        }
    }

    swap(arr[more], arr[right]);
    return {less + 1, more};
}

static void process(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    std::pair<int, int> equal_range = netherlandsFlag(arr, left, right);
    process(arr, left, equal_range.first - 1);
    process(arr, equal_range.second + 1, right);
}

static void QuickSort2(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    process(arr, 0, arr.size() -1);
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

//TEST(SortTest, QuickSort2RecurTest) {
//    cout << "quick sort2 recur test start\n";
//    int max_n = 100;
//    int min_val = -20;
//    int max_val = 30;
//    int test_times = 100000;
//    for (int i = 0; i < test_times; i++) {
//        vector<int> arr1;
//        vector<int> arr2;
//        RandomArr(arr1, max_n, min_val, max_val);
//        CopyArr(arr1, arr2);
//        QuickSort2(arr1);
//        std::sort(arr2.begin(), arr2.end());
//        if (!IsEqual(arr1, arr2)) {
//            Print(arr1);
//            Print(arr2);
//            ASSERT_TRUE(false);
//        }
//    }
//    cout << "test success\n";
//    cout << "quick sort2 recur test end\n\n";
//}