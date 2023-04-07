#include <iostream>
#include <vector>
#include <deque>
#include "random.h"
#include "common.h"
#include "arr_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

/*
    给定一个整型数组arr，和一个整数sum
    某个arr中的子数组sub，如果想达标，必须满足：
    sub中最大值 – sub中最小值 <= sum，
    返回arr中达标子数组的数量

    leetcode 相关题目
    1438. 绝对差不超过限制的最长连续子数组
    https://leetcode.cn/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
 */
static int num(vector<int>& nums, int sum) {
    if (nums.size() == 0) {
        return 0;
    }

    int ans = 0;
    deque<int> qmax;
    deque<int> qmin;

    int right = 0;
    int n = nums.size();
    for (int left = 0; left < n; ++left) {
        while (right < n) {
            while (!qmax.empty() && nums[qmax.back()] <= nums[right]) {
                qmax.pop_back();
            }
            qmax.push_back(right);
            while (!qmin.empty() && nums[qmin.back()] >= nums[right]) {
                qmin.pop_back();
            }
            qmin.push_back(right);

            if (nums[qmax.front()] - nums[qmin.front()] > sum) {
                break;
            } else {
                ++right;
            }
        }

        ans += right - left;

        if (qmax.front() == left) {
            qmax.pop_front();
        }
        if (qmin.front() == left) {
            qmin.pop_front();
        }
    }

    return ans;
}

static int test(vector<int>& nums, int sum) {
    if (nums.size() == 0) {
        return 0;
    }

    int ans = 0;
    int n = nums.size();
    for (int left = 0; left < n; ++left) {
        for (int right = left; right < n; ++right) {
            int min_val = nums[left];
            int max_val = nums[left];
            for (int i = left + 1; i <= right; ++i) {
                min_val = std::min(min_val, nums[i]);
                max_val = std::max(max_val, nums[i]);
            }
            if (max_val - min_val <= sum) {
                ++ans;
            }
        }
    }

    return ans;
}

//TEST(CLASS24_TEST, AllLessNumsSubArray) {
//    std::cout << "test start ..." << endl;
//    int test_times = 100000;
//    int min_val = -100;
//    int max_val = 100;
//    int max_n = 50;
//    int max_sum = 100;
//    for (int i = 0; i < test_times; ++i) {
//        vector<int> nums;
//        RandomArr(nums, max_n, min_val, max_val);
//        int sum = RandomVal(0, max_sum);
//        if (test(nums, sum) != num(nums, sum)) {
//            std::cout << "test failed !!!!" << endl;
//            break;
//        }
//    }
//
//    std::cout << "test end" << endl;
//}