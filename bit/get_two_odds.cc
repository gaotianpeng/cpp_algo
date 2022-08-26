#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "gtest/gtest.h"
#include "common.h"
#include "arr_tools.h"
using namespace std;
using namespace tools;

/*
	一个数组中有两种数出现了奇数次，其他数都出现了偶数次，找到这两种数并返回
		注：假设arr中所有数都为正数，如果找不至均返回-1
		传入数组的中数据合理性由外部保证
 */
static std::pair<int, int> GetOddNumber(const std::vector<int>& arr) {
	if (arr.size() < 2) {
		return {-1, -1};
	}

	int eor = 0;
	for (auto& elem: arr) {
		eor ^= elem;
	}

	int right_one = eor & (~eor + 1);
	int eor2 = 0;
	for (auto& elem: arr) {
		if ((elem & right_one) != 0) {
			eor2 ^= elem;
		}
	}

	int ret1 = eor2;
	int ret2 = eor ^ eor2;
	if (ret1 < ret2) {
		return {ret1, ret2};
	}
	return {ret2, ret1};
}

/*
 * for test
 */
static void RandomArray(vector<int>& out, int min_val, int max_val, int max_n) {
	int out_n = RandomEvenVal(0, max_n);
	if (out_n == 0) {
		return;
	}

	std::set<int> sets;
	int n_odd = RandomOddVal(1, out_n);
	int n_odd_val = RandomVal(min_val, max_val);
	sets.insert(n_odd_val);
	for (int i = 0; i < n_odd; ++i) {
		out.emplace_back(n_odd_val);
	}
	out_n -= n_odd;

	n_odd = RandomOddVal(1, out_n);
	n_odd_val = RandomVal(min_val, max_val);
	while (sets.find(n_odd_val) != sets.end()) {
		n_odd_val = RandomVal(min_val, max_val);
	}
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

static std::pair<int,int> test(const std::vector<int>& arr) {
	if (arr.size() < 2) {
		return {-1, -1};
	}

	std::map<int, int> map_;
	for (auto& elem : arr) {
		if (map_.find(elem) != map_.end()) {
			int cnt = map_[elem];
			map_.erase(elem);
			map_.insert({elem, cnt + 1});
		} else {
			map_.insert({elem, 1});
		}
	}

	std::vector<int> res;
	for (auto& elem: map_) {
		if (elem.second % 2 == 1) {
			res.push_back(elem.first);
		}
	}
	std::sort(res.begin(), res.end());

	return {res[0], res[1]};
}

//TEST(BitTest, GetPddTest) {
//    cout << "bit test start\n";
//	int test_times = 100;
//	int min_val = -100;
//	int max_val = 200;
//	int max_n = 10;
//	for (int i = 0; i < test_times; i++) {
//		vector<int> out;
//		RandomArray(out, min_val, max_val, max_n);
//		auto res = test(out);
//		if (GetOddNumber(out) != test(out)) {
//			Print(out);
//			auto res1 = GetOddNumber(out);
//			auto res2 = test(out);
//			cout << "<" << res1.first << "," << res1.second << ">" << std::endl;
//			cout << "<" << res2.first << "," << res2.second << ">" << std::endl;
//			ASSERT_TRUE(false);
//		}
//	}
//
//    cout << "test success\n";
//    cout << "bit test end\n\n";
//}