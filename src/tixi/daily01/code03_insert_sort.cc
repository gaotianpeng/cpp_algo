#include <iostream>
#include <vector>
#include <algorithm>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

static void InsertSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int N = arr.size();
    for (int i = 1; i < N; ++i) {
        for (int j = i; j > 0; --j) {
            if (arr[j] < arr[j-1]) {
                ArrayUtils::swap(arr, j, j-1);
            }
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
        vector<int> arr1, arr2;
        ArrayUtils::randomArray(arr1, max_n, min, max);
        ArrayUtils::copyArray(arr1, arr2);
        InsertSort(arr1);
        std::sort(arr2.begin(), arr2.end());
        if (!ArrayUtils::isEqual(arr1, arr2)) {
            ArrayUtils::printArray(arr1);
            ArrayUtils::printArray(arr2);
            success = false;
            break;
        }
    }

    cout << (success ? "success" : "failed") << endl;
    cout << "test end" << endl;
    return 0;
}