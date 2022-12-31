#include <iostream>
#include <vector>
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
        index++;
    }
    swap(arr[++less_equal], arr[right]);
    return less_equal;
}

static void processs(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = partition(arr, left, right);
    processs(arr, left, mid - 1);
    processs(arr, mid + 1, right);
}
/*
在arr[L..R]范围上，进行快速排序的过程：
    1）用arr[R]对该范围做partition，<= arr[R]的数在左部分并且保证arr[R]最后来到左部分的最后一个位置，记为M； <= arr[R]的数在右部分（arr[M+1..R]）
    2）对arr[L..M-1]进行快速排序(递归)
    3）对arr[M+1..R]进行快速排序(递归)
因为每一次partition都会搞定一个数的位置且不会再变动，所以排序能完成
 */
static void QuickSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    processs(arr, 0, arr.size() - 1);
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

//TEST(SortTest, QuickSortRecurTest) {
//    cout << "quick sort recur test start\n";
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
//    cout << "quick sort recur test end\n\n";
//}