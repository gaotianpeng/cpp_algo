#include <algorithm>
#include <iostream>
#include <random>
#include <stack>
#include <vector>
using namespace std;

/*
    for test
*/
namespace {

class Math {
public:
    static double random() {
        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_real_distribution<> distribution(0.0, 1.0);
        return distribution(engine);
    }
};

static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Math::random() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(Math::random() * (max_val - min_val + 1)) + min_val;
		out.emplace_back(val);
	}
}

static void CopyArray(const vector<int>& src, vector<int>& dst) {
	for (int i = 0; i < src.size(); i++) {
        dst.push_back(src[i]);
	}
}

static void PrintArr(const vector<int>& arr) {
    for (auto& elem: arr) {
        cout << elem << " ";
    }
    cout << endl;
}

static bool IsEqual(const vector<int>& arr1, const vector<int>& arr2) {
    if (arr1.size() != arr2.size()) {
        return false;
    }

    for (int i = 0; i < arr1.size(); ++i) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

static void Swap(vector<int>& arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
}  // namespace

struct Op {
    int left = -1;
    int right = -1;
    
    Op(int l, int r): left(l), right(r) {}
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
        if (arr[index] == arr[right]) {
            ++index;
        } else if (arr[index] < arr[right]) {
            Swap(arr, ++less, index);
            ++index;
        } else {
            Swap(arr, index, --more);
        }
    }

    Swap(arr, right, more);
    return {++less, more};
}

static void QuickSort(vector<int>& arr) {
    if (arr.size() < 2) {
        return;
    }

    int n = arr.size();
    std::pair<int, int> equal_area = partition(arr, 0, n - 1);
    stack<Op> ops;
    ops.push({0, equal_area.first - 1});
    ops.push({equal_area.second + 1, n - 1});

    while (!ops.empty()) {
        Op cur_op = ops.top();
        ops.pop();
        if (cur_op.left < cur_op.right) {
            std::pair<int, int> equal_area = partition(arr, cur_op.left, cur_op.right);
            ops.push({cur_op.left, equal_area.first - 1});
            ops.push({equal_area.second + 1, cur_op.right});
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
        CopyArray(arr1, arr2);
        QuickSort(arr1);
        std::sort(arr2.begin(), arr2.end());
        if (!IsEqual(arr1, arr2)) {
            PrintArr(arr1);
            cout << "test failed" << endl;
            break;
        }
    }

    cout << "test end" << endl;

    return 0;
}
