#include <iostream>
#include <vector>
#include <algorithm>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

/*
选择排序
    arr[0～N-1]范围上，找到最小值所在的位置，然后把最小值交换到0位置
    arr[1～N-1]范围上，找到最小值所在的位置，然后把最小值交换到1位置
    arr[2～N-1]范围上，找到最小值所在的位置，然后把最小值交换到2位置
    …
    arr[N-1～N-1]范围上，找到最小值位置，然后把最小值交换到N-1位置
*/
static void SelectSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int N = arr.size();
    for (int i = 0; i < N; ++i) {
        int min_index = i;
        for (int j = i + 1; j < N; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            ArrayUtils::swap(arr, i, min_index);
        }
    }
}

/*
    选择排序
        arr[0～N-1]范围上，找到最大值所在的位置，然后把最大值交换到 N-1 位置
        arr[0～N-2]范围上，找到最大值所在的位置，然后把最大值交换到 N-2 位置
        arr[0～N-3]范围上，找到最磊值所在的位置，然后把最大值交换到 M-3 位置
        …
        arr[0~0] 范围上，找到最大值位置，然后把最大值交换到 0 位置
*/
static void SelectSort1(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int n = arr.size();
    for (int i = n - 1; i > 0; i--) {
        int max_idx = i;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[max_idx]) {
                max_idx = j;
            }
        }

        if (max_idx != i) {
            ArrayUtils::swap(arr, max_idx, i);
        }
    }
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 100000;
    bool success = true;

    for (int i = 0; i < test_times; ++i) {
        vector<int> arr1, arr2, arr3;
        ArrayUtils::randomArray(arr1, max_n, min, max);
        ArrayUtils::copyArray(arr1, arr2);
        ArrayUtils::copyArray(arr1, arr3);
        SelectSort(arr1);
        std::sort(arr2.begin(), arr2.end());
        SelectSort1(arr3);
        if (!ArrayUtils::isEqual(arr1, arr2)) {
            ArrayUtils::printArray(arr1);
            ArrayUtils::printArray(arr2);
            success = false;
            break;
        }
        if (!ArrayUtils::isEqual(arr1, arr3)) {
            success = false;
            break;
        }
    }

    cout << (success ? "success" : "failed") << endl;
    cout << "test end" << endl;

    return 0;
}