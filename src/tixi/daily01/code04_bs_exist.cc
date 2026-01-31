#include <iostream>
#include <vector>
#include <algorithm>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

/*
    在一个有序数组中，找某个数是否存在
*/
static bool IsExist(vector<int>& arr, int target) {
    if (arr.size() < 1) {
        return false;
    }

    int left = 0;
    int right = arr.size() - 1;
    while (left < right) {
        int mid = left + ((right - left) >> 1);
        if (arr[mid] == target) {
            return true;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return arr[left] == target;
}

static bool test(vector<int>& arr, int target) {
    if (arr.size() == 0) {
        return false;
    }

    for (auto& elem: arr) {
        if (elem == target) {
            return true;
        }
    }

    return false;
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
        if (IsExist(arr, target) != test(arr, target)) {
            success = false;
            ArrayUtils::printArray(arr);
            cout << target << endl;
            break;
        }
    }

    cout << (success ? "success" : "failed") << endl;
    cout << "test end" << endl;
    return 0;
}