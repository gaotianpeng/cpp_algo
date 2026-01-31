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
}  // namespace

static int partition(vector<int>& arr, int left, int right) {
    if (left > right) {
        return -1;
    }

    if (left == right) {
        return left;
    }

    int less = left - 1;
    int index = left;
    while (index < right) {
        if (arr[index] <= arr[right]) {
            ArrayUtils::swap(arr, ++less, index);
        }

        ++index;
    }

    ArrayUtils::swap(arr, ++less, right);
    return less;
}

static void process(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int part_pos = partition(arr, left, right);
    process(arr, left, part_pos - 1);
    process(arr, part_pos + 1, right);
}

/*
    Partition过程
    给定一个数组arr，和一个整数num。请把小于等于num的数放在数组的左边，大于num的数放在数组的右边
*/
static void QuickSort(vector<int>& arr) {
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
    int test_times = 10;

    for (int i = 0; i < test_times; ++i) {
        vector<int> arr1, arr2;
        RandomArr(arr1, max_n, min, max);
        ArrayUtils::copyArray(arr1, arr2);
        QuickSort(arr1);
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