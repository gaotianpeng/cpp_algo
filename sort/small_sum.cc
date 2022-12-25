#include <array>
#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "arr_tools.h"

using namespace std;
using namespace tools;

/*
	在一个数组中，一个数左边比它小的数的总和，叫数的小和，所有数的小和累加起来，叫数组小和。求数组小和。
	例子： [1,3,4,2,5]
		1左边比1小的数：没有
		3左边比3小的数：1
		4左边比4小的数：1、3
		2左边比2小的数：1
		5左边比5小的数：1、3、4、 2
		所以数组的小和为1+1+3+1+1+3+4+2=16
 */
static int merge(vector<int>& arr, int left, int mid, int right) {
    int n = right - left + 1;
    int* helper = new int[n];
    int p1 = left;
    int p2 = mid + 1;
    int i = 0;
    int ans = 0;
    while (p1 <= mid && p2 <= right) {
        ans += arr[p1] < arr[p2] ? arr[p1] * (right - p2 + 1) : 0;
        helper[i++]  = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
    }

    while (p1 <= mid) {
        helper[i++] = arr[p1++];
    }
    while (p2 <= right) {
        helper[i++] = arr[p2++];
    }

    for (int i = 0; i < n; ++i) {
        arr[left + i] = helper[i];
    }

    delete [] helper;

    return ans;
}


static int SmallSum(vector<int> arr) {
    if (arr.size() < 2) {
        return 0;
    }

    int n = arr.size();
    int merge_size = 1;
    int ans = 0;
    while (merge_size < n) {
        int left = 0;
        while (left < n) {
            if (merge_size >= n - left) {
                break;
            }

            int mid = left + merge_size - 1;
            int right = mid + std::min(n - mid -1, merge_size);
            ans += merge(arr, left, mid, right);
            left = right + 1;
        }

        if (merge_size > n/2) {
            break;
        }
        merge_size <<= 1;
    }

    return ans;
}

static int test(vector<int>& arr) {
    if (arr.size() < 2) {
        return 0;
    }

    int ans = 0;
    for (int i = 1; i < arr.size(); ++i) {
        for(int j = 0; j < i; ++j) {
            if (arr[j] < arr[i]) {
                ans += arr[j];
            }
        }
    }

    return ans;
}

//TEST(SortTest, SmallSumTest) {
//    cout << "small sum test start\n";
//    int max_n = 100;
//    int min_val = 20;
//    int max_val = 50;
//    int test_times = 500000;
//    for (int i = 0; i < test_times; i++) {
//        vector<int> arr1;
//        vector<int> arr2;
//        RandomArr(arr1, max_n, min_val, max_val);
//        CopyArr(arr1, arr2);
//        int ans1 = test(arr1);
//        int ans2 = SmallSum(arr2);
//        if (ans1 != ans2) {
//            cout << ans1 << endl;
//            cout << ans2 << endl;
//            ASSERT_TRUE(false);
//        }
//    }
//    cout << "test success\n";
//    cout << "small sum test end\n\n";
//}