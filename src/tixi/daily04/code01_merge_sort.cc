#include <iostream>
#include <vector>
#include <algorithm>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

/*
    for test
*/
namespace {

static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Random::nextDouble() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(Random::nextDouble() * (max_val - min_val + 1)) + min_val;
		out.emplace_back(val);
	}
}

} // namespace


static void merge(vector<int>& arr, int left, int mid, int right) {
    int n = right - left + 1;
    int* helper = new int[n];
    int index = 0;
    int idx1 = left;
    int idx2 = mid + 1;
    while (idx1 <= mid && idx2 <= right) {
        helper[index++] = arr[idx1] <= arr[idx2] ? arr[idx1++]: arr[idx2++];
    }

    while (idx1 <= mid) {
        helper[index++] = arr[idx1++];
    }

    while (idx2 <= right) {
        helper[index++] = arr[idx2++];
    }

    for (int i = 0; i < n; ++i) {
        arr[left++] = helper[i];
    }

    delete []helper;
}

static void process(vector<int>& arr, int left, int right) {
    if (left == right) {
        return;
    }

    int mid = left + ((right - left) >> 1);
    process(arr, left, mid);
    process(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

static void MergeSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    process(arr, 0, arr.size() - 1);
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        vector<int> arr1, arr2;
        RandomArr(arr1, max_n, min, max);
        ArrayUtils::copyArray(arr1, arr2);
        MergeSort(arr1);
        std::sort(arr2.begin(), arr2.end());
        if (!ArrayUtils::isEqual(arr1, arr2)) {
            ArrayUtils::printArray(arr1);
            cout << "test failed" << endl;
            break;
        }
    }

    cout << "test end" << endl;

    return 0;
}