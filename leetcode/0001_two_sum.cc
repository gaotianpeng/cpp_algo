#include <iostream>
#include <vector>
#include <unordered_map>

namespace {
using namespace std;

/*
0001 两数之和
    给定一个整数数组 nums和一个整数目标值 target，请你在该数组中找出 和为目标值 target 的那两个整数，并返回它们的数组下标。
    你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
    你可以按任意顺序返回答案
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> elem_pos_map;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            auto iter = elem_pos_map.find(target - nums[i]);
            if (iter != elem_pos_map.end()) {
                return {i, iter->second};
            }
            elem_pos_map.insert({nums[i], i});
        }

        return {};
    }

    vector<int> twoSum1(vector<int>& nums, int target) {
        unordered_map<int, int> elem_pos_map;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            elem_pos_map.insert({nums[i], i});
        }

        for (int i = 0; i < n; ++i) {
            int elem = target - nums[i];
            auto iter = elem_pos_map.find(elem);
            if (iter != elem_pos_map.end()) {
                if (elem_pos_map[elem] != i) {
                    return {i, elem_pos_map[elem]};
                }
            }
        }

        return {};
    }
};

}  // namespace
