#include <iostream>
#include <vector>
#include <stack>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

/*
    Partition 过程
        给定一个数组 arr, 和一个整数 num. 请把小于等于 num 的数放在数组的左边，大于num的数放在数组的右边
        要求 额外空间复杂度为 O(1), 时间复杂度为 O(N)
*/
static int partition(vector<int>& arr, int left, int right) {
    if (left > right) {
        return -1;
    }

    if (left == right) {
        return left;
    }

    int less_equal = left - 1;
    int index = left;
    while (index < right) {
        if (arr[index] <= arr[right]) {
            swap(arr[index], arr[++less_equal]);
        }
        ++index;
    }

    swap(arr[right], arr[++less_equal]);
    return less_equal;
}

static void QuickSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int n = arr.size();
    stack<pair<int, int>> ranges;
    int mid = partition(arr, 0, n - 1);
    ranges.push({0, mid - 1});
    ranges.push({mid + 1, n-1});

    while (!ranges.empty()) {
        pair<int, int> range = ranges.top();
        ranges.pop();
        if (range.first < range.second) {
            int mid = partition(arr, range.first, range.second);
            ranges.push({range.first, mid - 1});
            ranges.push({mid + 1, range.second});
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

//TEST(SortTest, QuickSortTest) {
//    cout << "quick sort test start\n";
//    int max_n = 100;
//    int min_val = -20;
//    int max_val = 30;
//    int test_times = 100000;
//    for (int i = 0; i < test_times; i++) {
//        vector<int> arr1;
//        vector<int> arr2;
//        RandomArr(arr1, max_n, min_val, max_val);
//        CopyArr(arr1, arr2);
//        QuickSort(arr1);
//        std::sort(arr2.begin(), arr2.end());
//        if (!IsEqual(arr1, arr2)) {
//            Print(arr1);
//            Print(arr2);
//            ASSERT_TRUE(false);
//        }
//    }
//    cout << "test success\n";
//    cout << "quick sort test end\n\n";
//}