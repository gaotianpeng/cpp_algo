#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
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

struct Op {
    Op(int l, int r):left(l), right(r) {
    }

    int left = -1;
    int right = -1;
};

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
            ArrayUtils::swap(arr, --more, index);
        }
    }

    ArrayUtils::swap(arr, more, right);
    return {++less, more};
}

static void QuickSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    stack<Op> st;
    std::pair<int, int> area = partition(arr, 0, arr.size() - 1);
    st.push(Op(0, area.first - 1));
    st.push(Op(area.second + 1, arr.size() - 1));

    while (!st.empty()) {
        Op op = st.top();
        st.pop();
        if (op.left < op.right) {
            std::pair<int, int> area = partition(arr, op.left, op.right);
            st.push(Op(op.left, area.first - 1));
            st.push(Op(area.second + 1, op.right));  
        }
    }
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
