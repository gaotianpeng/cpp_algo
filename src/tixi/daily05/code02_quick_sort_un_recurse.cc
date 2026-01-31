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
    Op(int l, int r):left(l), right(r)  {
    }

    int left = -1;
    int right = -1;
};

static int partition(vector<int>& arr, int left, int right) {
    if (left > right ) {
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

/*
    Partition过程
    给定一个数组arr，和一个整数num。请把小于等于num的数放在数组的左边，大于num的数放在数组的右边
*/
static void QuickSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int part_pos = partition(arr, 0, arr.size() - 1);
    stack<Op> st;
    st.push(Op(0, part_pos - 1));
    st.push(Op(part_pos + 1, arr.size() - 1));
    while (!st.empty()) {
        Op op = st.top();
        st.pop();
        if (op.left < op.right) {
            int part_pos = partition(arr, op.left, op.right);
            st.push(Op(op.left, part_pos - 1));
            st.push(Op(part_pos + 1, op.right));
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