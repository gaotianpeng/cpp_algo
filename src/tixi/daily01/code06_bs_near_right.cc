#include <iostream>
#include <vector>
#include <algorithm>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

/*
    在一个有序数组中，找<=某个数最右侧的位置
*/
static int RightNearestIndex(vector<int>& arr, int target) {
    if (arr.size() == 0) {
        return -1;
    }

    int ans = -1;
    int left = 0;
    int right = arr.size() -1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        if (arr[mid] <= target) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }

    }
    return ans;
}

static int test(vector<int>& arr, int target) {
    if (arr.size() == 0) {
        return -1;
    }

    int ans = -1;
    int n = arr.size();
    for (int i = n - 1; i >= 0; --i) {
        if (arr[i] <= target) {
            ans = i;
            break;
        }
    }
    return ans;
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 100000;
    bool success = true;

    for (int i = 0; i < test_times; ++i) {
        vector<int> arr;
        ArrayUtils::randomArray(arr, max_n, min, max);
        std::sort(arr.begin(), arr.end());
        int target = Random::nextInt(min, max);
        int ans1 = RightNearestIndex(arr, target);
        int ans2 = test(arr, target);
        if (ans1 != ans2) {
            success = false;
            ArrayUtils::printArray(arr);
            break;
        }
    }

    cout << (success ? "success" : "failed") << endl;
    cout << "test end" << endl;
    return 0;
}