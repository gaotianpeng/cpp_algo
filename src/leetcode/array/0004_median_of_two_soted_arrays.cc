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

// Custom RandomArr that returns sorted array
static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
    int len = std::max(2, (int)(Random::nextDouble() * max_n));
    for (int i = 0; i < len; i++) {
        int val = Random::nextInt(min_val, max_val);
        out.emplace_back(val);
    }
    std::sort(out.begin(), out.end());
}

} // namespace

/*
    https://leetcode.cn/problems/two-sum/
    0004 寻找两个正序数组的中位数
    给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数
    算法的时间复杂度应该为 O(log (m+n)) 
*/
static int getUpMedian(const vector<int>& nums1, int start1, int end1,
        const vector<int>& nums2, int start2, int end2) {
    int mid1 = 0;
    int mid2 = 0;

    while (start1 < end1) {
        mid1 = (start1 + end1) / 2;
        mid2 = (start2 + end2) / 2;

        if (nums1[mid1] == nums2[mid2]) {
            return nums1[mid1];
        }

        if (((end1 - start1 + 1) & 1) == 1) { // 奇数长度
            if (nums1[mid1] > nums2[mid2]) {
                if (nums2[mid2] >= nums1[mid1-1]) {
                    return nums2[mid2];
                }
                
                end1 = mid1 - 1;
                start2 = mid2 + 1;
            } else {
                if (nums1[mid1] >= nums2[mid2 - 1]) {
                    return nums1[mid1];
                }
                start1 = mid1 + 1;
                end2 = mid2 - 1;
            }
            
        } else { // 偶数长度
            if (nums1[mid1] > nums2[mid2]) {
                end1 = mid1;
                start2 = mid2 + 1;
            } else {
                start1 = mid1 + 1;
                end2 = mid2;
            }
        }
    }

    
    return std::min(nums1[start1], nums2[start2]);
}

static int findKthNum(const vector<int>& nums1, const vector<int>& nums2, int kth) {
    const vector<int>& long_arr = nums1.size() >= nums2.size() ? nums1 : nums2;
    const vector<int>& short_arr = nums1.size() < nums2.size() ? nums1 : nums2;
    int long_len = long_arr.size();
    int short_len = short_arr.size();

    if (kth <= short_len) {
        return getUpMedian(short_arr, 0, kth - 1, long_arr, 0, kth - 1);
    }

    if (kth > long_len) {
        if (short_arr[kth - long_len - 1] >= long_arr[long_len - 1]) {
            return short_arr[kth - long_len - 1];
        }
        
        if (long_arr[kth - short_len - 1] >= short_arr[short_len - 1]) {
            return long_arr[kth - short_len - 1];
        }

        return getUpMedian(short_arr, kth - long_len, short_len - 1, 
                    long_arr, kth - short_len, long_len - 1);
    }

    if (long_arr[kth - short_len - 1] >= short_arr[short_len - 1]) {
        return long_arr[kth - short_len - 1];
    }

    return getUpMedian(short_arr, 0, short_len - 1, long_arr, kth - short_len, kth - 1);
}


double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int size = nums1.size() + nums2.size();
    bool even = (size & 1) == 0;
    if (nums1.size() != 0 && nums2.size() != 0) {
        if (even) {
            return (double)(findKthNum(nums1, nums2, size / 2) + 
                findKthNum(nums1, nums2, size / 2 + 1)) / 2;
        } else {
            return findKthNum(nums1, nums2, size / 2 + 1);
        }
    } else if (nums1.size() != 0) {
        if (even) {
            return (double)(nums1[(size - 1) / 2] + nums1[size / 2]) / 2;
        } else {
            return nums1[size / 2];
        }
    } else if (nums2.size() != 0) {
        if (even) {
            return (double)(nums2[(size - 1) / 2] + nums2[size / 2]) / 2;
        } else {
            return nums2[size / 2];
        }
    } else {
        return 0;
    }
}

double test(vector<int>& nums1, vector<int>& nums2) {
    vector<int> all_nums;
    for (auto& elem: nums1) {
        all_nums.emplace_back(elem);
    }

    for (auto& elem: nums2) {
        all_nums.emplace_back(elem);        
    }

    std::sort(all_nums.begin(), all_nums.end());
    int n = all_nums.size();
    if (n % 2 == 1) {
        return (double)all_nums[n/2];
    } else {
        return (double)(all_nums[n/2 -1] + all_nums[n/2])/2;
    }
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 20;
    int min = -20;
    int max_n = 30;
    int test_times = 50000;

    for (int i = 0; i < test_times; ++i) {
        vector<int> nums1;
        vector<int> nums2;

        RandomArr(nums1, max_n, min, max);
        RandomArr(nums2, max_n, min, max);

        double ans1 = findMedianSortedArrays(nums1, nums2);
        double ans2 = test(nums1, nums2);

        if (ans1 != ans2) {
            cout << "test failed " << std::endl;
            break;
        }
    }

    cout << "test end" << endl;

    return 0;
}
