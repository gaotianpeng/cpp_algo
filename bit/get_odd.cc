#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "gtest/gtest.h"
#include "common.h"
#include "arr_tools.h"
using namespace std;
using namespace tools;

// 一个数组中有一种数出现了奇数次，其他数都出现了偶数次，找到这种数
static int GetOddNumber(const std::vector<int>& arr) {
	int eor = 0;
	for (int i = 0; i < arr.size(); i++) {
		eor ^= arr[i];
	}
	return eor;
}

/*
 * for test
 */
static void RandomArray(vector<int>& out, int min_val, int max_val, int max_n) {
	int out_n = RandomVal(0, max_n);
	if (out_n == 0) {
		return;
	}
	while ((out_n & 1) == 0) {
		out_n = RandomVal(0, max_n);
	}


	int n_odd = RandomOddVal(1, out_n);
	std::set<int> sets;
	int n_odd_val = RandomVal(min_val, max_val);
	sets.insert(n_odd_val);
	for (int i = 0; i < n_odd; ++i) {
		out.emplace_back(n_odd_val);
	}

	out_n -= n_odd;
	while (out_n > 0) {
		int n_even = RandomEvenVal(0, out_n);
		int n_even_val = RandomVal(min_val, max_val);
		while (sets.find(n_even_val) != sets.end()) {
			n_even_val = RandomVal(min_val, max_val);
		}
		for (int i = 0; i < n_even; ++i) {
			out.emplace_back(n_even_val);
		}
		out_n -= n_even;
	}

	for (int i = 0; i < out.size(); i++) {
		int pos1 = RandomVal(0, out.size() - 1);
		int pos2 = RandomVal(0, out.size() - 1);
		if (pos1 != pos2) {
			Swap(out[pos1], out[pos2]);
		}
	}
}

static int test(const std::vector<int>& arr) {
	std::map<int, int> map_;
	for (auto& elem: arr) {
		if (map_.find(elem) != map_.end()) {
			map_.insert({elem, map_[elem] + 1});
			int cnt = map_[elem];
			map_.erase(elem);
			map_.insert({elem, cnt + 1});
		} else {
			map_.insert({elem, + 1});
		}
	}

	int eor = 0;
	for (auto & elem: map_) {
		if (map_[elem.first] % 2 == 1) {
			eor = elem.first;
		}
	}
	return eor;
}

//TEST(BitTest, GetPddTest) {
//    cout << "bit test start\n";
//	int test_times = 500000;
//	int min_val = -100;
//	int max_val = 200;
//	int max_n = 30;
//	for (int i = 0; i < test_times; i++) {
//		vector<int> out;
//		RandomArray(out, min_val, max_val, max_n);
//		if (GetOddNumber(out) != test(out)) {
//			Print(out);
//			cout << GetOddNumber(out) << endl;
//			cout << test(out) << endl;
//			ASSERT_TRUE(false);
//		}
//	}
//
//    cout << "test success\n";
//    cout << "bit test end\n\n";
//}