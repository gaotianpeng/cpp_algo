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
static int CountRangeSum(std::vector<int> arr, int lower, int upper) {
    return 0;
}


static bool CheckValid(int64_t val, int lower, int upper) {
    return val <= upper && val >= lower;
}

static int test(std::vector<int> arr, int lower, int upper) {
    if (arr.size() < 1) {
        return 0;
    }

    int n = arr.size();
    int64_t pre_sum[n+1];
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

TEST(SortTest, CountRangeSumTest) {
    std::cout << "count range sum test start" << std::endl;
    int max_val = 100;
    int min_val = -100;
    int max_n = 50;
    int test_times = 500000;
    int max_range_val = 300;
    for (int i = 0; i  < test_times; ++i) {
        vector<int> arr1;
        vector<int> arr2;
        RandomArr(arr1, max_n, min_val, max_val);
        CopyArr(arr1, arr2);
        std::pair<int, int> range = GenerateRange(max_range_val);
        if (test(arr1, range.first, range.second) !=
                CountRangeSum(arr2, range.first, range.second)) {
            Print(arr1);
            ASSERT_TRUE(false);
        }
    }

    std::cout << "test success" << std::endl;
    std::cout << "count range sum test end" << std::endl;
}