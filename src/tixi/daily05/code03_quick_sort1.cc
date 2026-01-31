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

static std::pair<int, int> partition(vector<int>& arr, int left, int right) {
    if (left > right) {
        return {-1, -1};
    }

    if (left == right) {
        return {left, left};
    }

    int less = left - 1;
    int more = right;
    int index = left;
    while (index < more) {
        if (arr[index] < arr[right]) {
            ArrayUtils::swap(arr, ++less, index++);
        } else if (arr[index] == arr[right]) {
            ++index;
        } else {
            ArrayUtils::swap(arr, index, --more);
        }
    }

    ArrayUtils::swap(arr, more, right);
    return {++less, more};
}


static void process(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    std::pair<int, int> equal_area = partition(arr, left, right);
    process(arr, left, equal_area.first - 1);
    process(arr, equal_area.second + 1, right);
}

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
    int test_times = 50000;

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
