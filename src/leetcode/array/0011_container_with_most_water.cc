#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

namespace {

// Custom RandomArr that returns vector<int>
static vector<int> RandomArr(int max_len, int min, int max) {
    int len = Random::nextInt(0, max_len);
    vector<int> ans;
    for (int i = 0; i < len; ++i) {
        ans.emplace_back(Random::nextInt(min, max));
    }

    return ans;
}

} // namespace

/*
    https://leetcode.cn/problems/container-with-most-water/
    11. 盛最多水的容器
    给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
    找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
    返回容器可以储存的最大水量。
    说明：你不能倾斜容器。
*/
static int maxArea(vector<int>& height) {
    int ans = 0;
    int l = 0;
    int r = height.size() - 1;
    while (l < r) {
        ans = std::max(ans, std::min(height[l], height[r]) * (r - l));
        if (height[l] > height[r]) {
            r--;
        } else {
            l++;
        }
    }
    return ans;
}

static int test(vector<int>& height) {
    int ans = 0;
    int n = height.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ans = std::max(ans, std::min(height[i], height[j]) * (j - i));
        }
    }

    return ans;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int test_time = 100000;
    int max_n = 300;
    int min = 0;
    int max = 20;

    for (int i = 0; i < test_time; ++i) {
        vector<int> height = RandomArr(max_n, min, max);
        if (maxArea(height) != test(height)) {
            cout << "test failed" << endl;
            break;
        }
    }

    cout << "test end" << endl;
    return 0;
}