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
 *  一个数组中一种数出现k次，其它数都出现了M次
 *  M > 1, K < M
 *  找到出现了K次的数
 *  要求, 额外空间复杂度为O(1), 时间复杂度为O(N)
 *  说明，请外部保证数据的合法性(k>0)
 */
static int FindKM(const std::vector<int>& arr, int k, int m) {
	if (arr.size() < k + m) {
		return -1;
	}

	map<int, int> bit_one;
	int int_bits = sizeof(int)*8;
	int val = 1;
	for (int i = 0; i < int_bits; ++i) {
		bit_one.insert({val, i});
		val <<= 1;
	}

	vector<int> bits_one_sum(int_bits, 0);
	for (auto elem: arr) {
		while (elem != 0) {
			int right_one = elem & (-elem);
			bits_one_sum[bit_one[right_one]]++;
			elem ^= right_one;
		}
	}

	int ans = 0;
	for (int i = 0; i < int_bits; i++) {
		if ((bits_one_sum[i] % m) != 0) {
			ans |= (1<<i);
		}
	}

	return ans;
}

/*
 * for test
 */
// min_val < max_val 由外部保证
std::pair<int, int> RandomKM(int min_val, int max_val) {
	if (min_val <= 1) {
		min_val = 2;
	}
	int m = RandomVal(min_val, max_val);
	int k = RandomVal(1, m - 1);
	return {k, m};
}


/*
 * for test
 */
// min_val < max_val , k < m, max_n > k + m 由外部保证
static void RandomArray(vector<int>& out, int min_val, int max_val, int max_n, int k, int m) {
	int arr_len = RandomVal(k + m, max_n);
	while (((arr_len - k) % m) != 0) {
		arr_len = RandomVal(k+m, max_n);
	}

	set<int> keys;
	int k_val = RandomVal(min_val, max_val);
	keys.insert(k_val);
	for(int i = 0; i < k; ++i) {
		out.emplace_back(k_val);
	}

	arr_len -= k;
	while (arr_len > 0) {
		int m_val = RandomVal(min_val, max_val);
		while (keys.find(m_val) != keys.end()) {
			m_val = RandomVal(min_val, max_val);
		}
		keys.insert(m_val);
		for (int i = 0; i < m; i++) {
			out.push_back(m_val);
		}
		arr_len -= m;
	}

	for (int i = 0; i < out.size(); i++) {
		int pos1 = RandomVal(0, out.size() - 1);
		int pos2 = RandomVal(0, out.size() - 1);
		if (pos1 != pos2) {
			Swap(out[pos1], out[pos2]);
		}
	}
}

static int test(const std::vector<int>& arr, int k, int m) {
	if (arr.size() < k + m) {
		return -1;
	}

	map<int, int> map_;
	for (auto& elem: arr) {
		if (map_.find(elem) != map_.end()) {
			int cnt = map_[elem];
			map_.erase(elem);
			map_.insert({elem, cnt + 1});
		} else {
			map_.insert({elem, 1});
		}
	}

	for (auto& elem: map_) {
		if (elem.second == k) {
			return elem.first;
		}
	}

	return -1;
}

//TEST(BitTest, GetPddTest) {
//    cout << "bit test start\n";
//	int test_times = 500000;
//	int min_val = -100;
//	int max_val = 200;
//	int max_n = 50;
//	int min_km = 1;
//	int max_km = 10;
//	for (int i = 0; i < test_times; i++) {
//		pair<int, int> km = RandomKM(min_km, max_km);
//		vector<int> arr;
//		RandomArray(arr, min_val, max_val, max_n, km.first, km.second);
//		if (test(arr, km.first, km.second) != FindKM(arr, km.first, km.second))  {
//			Print(arr);
//			cout << "k, m = (" << km.first << "," << km.second << ")" << endl;
//			cout << test(arr, km.first, km.second) << endl;
//			cout << FindKM(arr, km.first, km.second) << endl;
//			ASSERT_TRUE(false);
//		}
//	}
//
//    cout << "test success\n";
//    cout << "bit test end\n\n";
//}