#include <iostream>
#include <vector>
#include "common.h"
#include "arr_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

/*
    给定一个数组arr，两个整数lower和upper，
    返回arr中有多少个子数组的累加和在[lower,upper]范围上
 */
static int merge(int64_t sum[], int left, int mid, int right, int lower, int upper) {
    int ans = 0;
    int win_left = left;
    int win_right = left;
    for (int i = mid + 1; i <= right; ++i) {
        int64_t min = sum[i] - upper;
        int64_t max = sum[i] - lower;
        while (win_right <= mid && sum[win_right] <= max) {
            win_right++;
        }
        while (win_left <= mid && sum[win_left] < min) {
            win_left++;
        }

        ans += win_right - win_left;
    }

    int n = right - left + 1;
    int64_t* helper = new int64_t[n] {0};
    int left_index = left;
    int right_index = mid + 1;
    int index = 0;
    while (left_index <= mid && right_index <= right) {
        helper[index++] = sum[left_index] <= sum[right_index] ?
                sum[left_index++] : sum[right_index++];
    }

    while (left_index <= mid) {
        helper[index++] = sum[left_index++];
    }

    while (right_index <= right) {
        helper[index++] = sum[right_index++];
    }

    for (int i = 0; i < n; ++i) {
        sum[left + i] = helper[i];
    }

    delete [] helper;

    return ans;
}

static bool CheckValid(int64_t val, int lower, int upper) {
    return val <= upper && val >= lower;
}

static int process(int64_t sum[], int left, int right, int lower, int upper) {
    if (left == right) {
        return CheckValid(sum[left], lower, upper) == true ? 1: 0;
    }

    int mid = left + ((right - left) >> 1);
    return process(sum, left, mid, lower, upper)
            + process(sum, mid + 1, right , lower, upper)
            + merge(sum, left, mid, right, lower, upper);
}

static int CountRangeSum(std::vector<int> arr, int lower, int upper) {
    if (arr.size() < 1) {
        return 0;
    }

    int ans = 0;
    int64_t* pre_sum = new int64_t[arr.size()];
    pre_sum[0] = arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        pre_sum[i] = pre_sum[i-1] + arr[i];
    }

    ans = process(pre_sum, 0, arr.size() - 1, lower, upper);

    delete [] pre_sum;
    return ans;
}

static int test(std::vector<int> arr, int lower, int upper) {
    if (arr.size() < 1) {
        return 0;
    }

    int n = arr.size();
    int64_t* pre_sum = new int64_t[n+1] {0};
    int ans = 0;
    pre_sum[0]  = 0;
    pre_sum[1]  = arr[0];
    for (int i = 1; i < n; ++i) {
        pre_sum[i+1] = pre_sum[i] + arr[i];
    }

    for(int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int64_t sum = pre_sum[j+1] - pre_sum[i];
            if (CheckValid(sum, lower, upper)) {
                ans += 1;
            }
        }
    }

    delete [] pre_sum;

    return ans;
}


static std::pair<int, int> GenerateRange(int max_val) {
    int upper = RandomVal(-max_val, max_val);
    int lower = RandomVal(-max_val, max_val);
    if (upper < lower) {
        return {upper, lower};
    }
    return {lower, upper};
}

//TEST(SortTest, CountRangeSumRecurTest) {
//    std::cout << "count range sum recur test start" << std::endl;
//    int max_val = 100;
//    int min_val = -100;
//    int max_n = 50;
//    int test_times = 500000;
//    int max_range_val = 300;
//    for (int i = 0; i  < test_times; ++i) {
//        vector<int> arr1;
//        vector<int> arr2;
//        RandomArr(arr1, max_n, min_val, max_val);
//        CopyArr(arr1, arr2);
//        std::pair<int, int> range = GenerateRange(max_range_val);
//        if (test(arr1, range.first, range.second) !=
//                CountRangeSum(arr2, range.first, range.second)) {
//            Print(arr1);
//            ASSERT_TRUE(false);
//        }
//    }
//
//    std::cout << "test success" << std::endl;
//    std::cout << "count range sum recur test end" << std::endl;
//}