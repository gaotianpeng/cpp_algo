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
    假设一个固定大小为W的窗口，依次划过arr，
    返回每一次滑出状况的最大值
            例如，arr = [4,3,5,4,3,3,6,7], W = 3
    返回：[5,5,5,4,6,7]
 */

static vector<int> GetMaxWindow(const vector<int>& arr, int w) {
    if (arr.size() == 0 || w < 1 || arr.size() < w) {
        return {};
    }

    int n = arr.size();
    vector<int> ans(n-w+1);
    deque<int> qmax;
    int index = 0;
    for (int right = 0; right < n; ++right) {
        while (!qmax.empty() && arr[qmax.back()] <= arr[right]) {
            qmax.pop_back();
        }

        qmax.push_back(right);
        if (qmax.front() == right - w) {
            qmax.pop_front();
        }

        if (right >= w - 1) {
            ans[index++] = arr[qmax.front()];
        }
    }


    return ans;
}

static vector<int> test(const vector<int>& arr, int w) {
    if (arr.size() == 0 || w < 1 || arr.size() < w) {
        return {};
    }

    int n = arr.size();
    vector<int> ans(n - w + 1);
    int index = 0;
    int left = 0;
    int right = w - 1;
    while (right < n) {
        int max = arr[left];
        for (int i = left + 1; i <= right; ++i) {
            max = std::max(max, arr[i]);
        }
        ans[index++] = max;
        ++left;
        ++right;
    }

    return ans;
}


//TEST(PractiseTest, SlidingWindowMaxArrayTest) {
//    cout << "sliding window max array test start\n";
//    int test_times = 100000;
//    int max_val = 100;
//    int min_val = 0;
//    int max_n  = 100;
//    bool success = true;
//    for (int i = 0; i < test_times; ++i) {
//        vector<int> arr;
//        RandomArr(arr, max_n, min_val, max_val);
//        int w = RandomVal(0, arr.size());
//        vector<int> ans1 = test(arr, w);
//        vector<int> ans2 = GetMaxWindow(arr, w);
//        if (!IsEqual(ans1, ans2)) {
//            success = false;
//            cout << w << endl;
//            Print(arr);
//            Print(ans1);
//            Print(ans2);
//            break;
//        }
//
//    }
//
//    cout << (success == true  ? "test success\n" : "test failed");
//    cout << "sliding window max array test end\n";
//}

}  // namespace