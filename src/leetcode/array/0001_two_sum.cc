#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include "common/test_utils.h"
using namespace std;
using namespace test_utils;

/*
    for test
*/
namespace {

// Custom IsEqual for two-sum problem (order doesn't matter)
static bool IsEqual(const vector<int>& arr1, const vector<int>& arr2) {
    if (arr1.size() != arr2.size()) {
        return false;
    }

    if (arr1[0] == arr2[1] && arr1[1] == arr2[0]) {
        return true;
    }

    if (arr1[0] == arr2[0] && arr1[1] == arr2[1]) {
      return true;  
    } 

    return false;
}

} // namespace

/*
    https://leetcode.cn/problems/two-sum/
    给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target的那两个整数，并返回它们的数组下标。
    你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
    你可以按任意顺序返回答案。
*/
static vector<int> twoSum(vector<int>& nums, int target) {
    // <val, pos>
    std::map<int, int> val_pos_map;

    for (int i = 0; i < nums.size(); ++i) {
        auto iter = val_pos_map.find(target - nums[i]);
        if (iter != val_pos_map.end()) {
            return {iter->second, i};
        }

        val_pos_map.insert({nums[i], i});
    }

    return {-1, -1};
}

static vector<int> test(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }

    return {-1, -1};
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 20;
    int min = -20;
    int max_n = 30;
    int test_times = 50000;

    for (int i = 0; i < test_times; ++i) {
        vector<int> arr1;
        vector<int> arr2;
        ArrayUtils::randomArray(arr1, max_n, min, max);
        ArrayUtils::copyArray(arr1, arr2);
        int target = Random::nextInt(min, max);

        vector<int> ans1 = twoSum(arr1, target);
        vector<int> ans2 = twoSum(arr2, target);
        if (!IsEqual(ans1, ans2)) {
            cout << "test failed" << endl;
            break;
        }
        
    }

    cout << "test end" << endl;

    return 0;
}
