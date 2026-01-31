#include <iostream>
#include <vector>
#include <algorithm>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

/*
    在一个有序数组中，找>=某个数最左侧的位置
*/
static int LeftNearestIndex(vector<int>& arr, int target) {
    if (arr.size() == 0) {
        return -1;
    }

    int N = arr.size();
    int left = 0;
    int right = N-1;
    int ans = -1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        if (arr[mid] >= target) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
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
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= target) {
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
        int ans1 = LeftNearestIndex(arr, target);
        int ans2 = test(arr, target);
        if (ans1 != ans2) {
            ArrayUtils::printArray(arr);
            cout << target << endl;
            success = true;
            break;
        }
    }

    cout << (success ? "success" : "failed") << endl;
    cout << "test end" << endl;
    return 0;
}