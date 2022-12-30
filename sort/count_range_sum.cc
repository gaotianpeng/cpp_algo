#include <iostream>
#include <vector>
#include <algorithm>
#include "common.h"
#include "arr_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

/*
    给定一个数组arr，两个整数lower和upper，
    返回arr中有多少个子数组的累加和在[lower,upper]范围上
 */
static bool CheckValid(int64_t val, int lower, int upper) {
    return val <= upper && val >= lower;
}

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

static int CountRangeSum(std::vector<int> arr, int lower, int upper) {
    if (arr.size() < 1) {
        return 0;
    }

    int ans = 0;
    int n = arr.size();
    int64_t* pre_sum = new int64_t[n] {0};
    pre_sum[0] = arr[0];
    for (int i = 1; i < n; ++i) {
        pre_sum[i] = pre_sum[i-1] + arr[i];
    }

    for (int i = 0; i < n; ++i) {
        ans += CheckValid(pre_sum[i], lower, upper) == true ? 1 : 0;
    }

    int merge_size = 1;
    while (merge_size < n) {
        int left = 0;
        while (left < n) {
            if (merge_size > n - left) {
                break;
            }

            int mid = left + merge_size - 1;
            int right = mid + std::min(merge_size, n - mid - 1);
            ans += merge(pre_sum, left, mid, right, lower, upper);
            left = right + 1;
        }

        if (merge_size > n/2) {
            break;
        }
        merge_size <<= 1;
    }


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

//TEST(SortTest, CountRangeSumTest) {
//    std::cout << "count range sum test start" << std::endl;
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
//        int ans1 = test(arr1, range.first, range.second);
//        int ans2 = CountRangeSum(arr2, range.first, range.second);
//        if (ans1 != ans2) {
//            Print(arr1);
//            std::cout << ans1 << std::endl;
//            std::cout << ans2 << std::endl;
//            ASSERT_TRUE(false);
//        }
//    }
//
//    std::cout << "test success" << std::endl;
//    std::cout << "count range sum test end" << std::endl;
//}