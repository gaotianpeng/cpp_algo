#include <algorithm>
#include <iostream>
#include <random>
#include <map>
#include <vector>
using namespace std;

/*
    for test
*/
namespace {

class Math {
public:
    static double random() {
        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_real_distribution<> distribution(0.0, 1.0);
        return distribution(engine);
    }
};


static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
    int len = std::max(2, (int)(Math::random() * max_n));
    for (int i = 0; i < len; i++) {
        int val = (int)(Math::random() * (max_val - min_val + 1)) + min_val;
        out.emplace_back(val);
    }
    std::sort(out.begin(), out.end());
}

static void CopyArray(const vector<int>& src, vector<int>& out) {
    for (int i = 0; i < src.size(); i++) {
       out.emplace_back(src[i]); 
    }
}

static int RandomVal(int min, int max) {
    return (int)(Math::random()*(max - min + 1)) + min;
}


} // namespace

/*
    https://leetcode.cn/problems/two-sum/
    0004 寻找两个正序数组的中位数
    给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数
    算法的时间复杂度应该为 O(log (m+n)) 
*/
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    
    return 0.0;
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
