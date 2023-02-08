#include <iostream>
#include <algorithm>
#include <queue>
#include "common.h"
#include "random.h"
#include "arr_tools.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

namespace {
/*
    给定一个整型数组arr，和一个整数num
            某个arr中的子数组sub，如果想达标，必须满足：
    sub中最大值 – sub中最小值 <= num，
    返回arr中达标子数组的数量
*/
static int GetAllLessNumSubArrayNum(const vector<int>& arr, int sum) {
    if (arr.empty() || sum < 0) {
        return 0;
    }

    int count = 0;
    int n = arr.size();
    std::deque<int> qmax;
    std::deque<int> qmin;
    int right = 0;
    for(int left = 0; left < n; ++left) {
        while (right < n) {
            while (!qmax.empty() && arr[qmax.back()] <= arr[right]) {
                qmax.pop_back();
            }
            qmax.push_back(right);
            while (!qmin.empty() && arr[qmin.back()] >= arr[right]) {
                qmin.pop_back();
            }
            qmin.push_back(right);

            if (arr[qmax.front()] - arr[qmin.front()] > sum) {
                break;
            } else {
                ++right;
            }

            count += right - left;
            if (qmax.front() == left) {
                qmax.pop_front();
            }
            if (qmin.front() == left) {
                qmin.pop_front();
            }
        }
    }

    return count;
}

static int test(const vector<int>& arr, int sum) {
    if (arr.empty() || sum < 0) {
        return 0;
    }

    int count = 0;
    int n = arr.size();
    for (int left = 0; left < n; ++left) {
        for (int right = left; right < n; ++right) {
            int cur_max = arr[left];
            int cur_min = arr[left];
            for (int i = left + 1; i <= right; ++i) {
                cur_max = std::max(cur_max, arr[i]);
                cur_min = std::min(cur_min, arr[i]);
            }
            if (cur_max - cur_min <= sum) {
                ++count;
            }
        }
    }

    return count;
}

//TEST(PractiseTest, AllLessNumSubArray) {
//    cout << "all less num sub array test start\n";
//    int test_times = 200;
//    int max_val = 100;
//    int min_val = 0;
//    int max_n  = 100;
//    bool success = true;
//    for (int i = 0; i < test_times; ++i) {
//        vector<int> arr;
//        RandomArr(arr, max_n, min_val, max_val);
//        int sum = RandomVal(0, max_val);
//        int ans1 = test(arr, sum);
//        int ans2 = GetAllLessNumSubArrayNum(arr, sum);
//        if (ans1 != ans2) {
//            success = false;
//            break;
//        }
//    }
//
//    cout << (success == true  ? "test success\n" : "test failed");
//    cout << "all less num sub array test end\n";
//}

}  // namespace