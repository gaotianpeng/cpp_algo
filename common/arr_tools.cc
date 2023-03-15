#include "arr_tools.h"
#include "random.h"
#include <iostream>
#include <algorithm>
#include <set>

using std::vector;
using std::cout;
using std::endl;

namespace tools {

void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Random::random() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(Random::random() * (max_val - min_val)) + min_val;
		out.emplace_back(val);
	}
}

void RandomSortedArr(std::vector<int>& out, int max_n, int min_val, int max_val) {
	RandomArr(out, max_n, min_val, max_val);
	std::sort(out.begin(), out.end());
}

void RandomNorepeatedArr(std::vector<int>& out, int max_n, int min_val, int max_val) {
    vector<int> elems;
    RandomArr(elems, max_n, min_val, max_val);
    std::set<int> vals;
    for (auto& elem :elems) {
        vals.insert(elem);
    }
    for (auto val: vals) {
        out.push_back(val);
    }
}

void CopyArr(const vector<int>& src, vector<int>& dst) {
	dst.clear();
	for (size_t i = 0; i < src.size(); i++) {
		dst.push_back(src[i]);
	}
}

void Print(const vector<int>& arr) {
	for (auto& elem: arr) {
		cout << elem << " ";
	}
	cout << endl;
}

bool IsEqual(const vector<int>& arr_a, const vector<int>& arr_b) {
	if (arr_a.size() != arr_b.size()) {
		return false;
	}

	int n = arr_a.size();
	for (int i = 0; i < n; i++) {
		if (arr_a[i] != arr_b[i]) {
			return false;
		}
	}

	return true;
}

bool IsReverse(const vector<int>& arr_a, const vector<int>& arr_b) {
	if (arr_a.size() != arr_b.size()) {
		return false;
	}

	int n = arr_a.size();
	for (int i = 0; i < n; i++) {
		if (arr_a[i] != arr_b[n-i-1]) {
			return false;
		}
	}

	return true;
}

} // namespace tools


