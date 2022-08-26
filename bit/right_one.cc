#include <iostream>
#include <bitset>
#include <numeric>
#include "gtest/gtest.h"
#include "common.h"
using namespace std;
using namespace tools;

static int GetRightOne(int n) {
	return n & (~n+1);
}

static int test(int n) {
	string str = bitset<sizeof(int)*8>(n).to_string();
	int right_one_idx = -1;
	for (int i = str.size() - 1; i >= 0; i--) {
		if (str[i] == '1') {
			right_one_idx =str.size() - 1 - i;
			break;
		}
	}

	if (right_one_idx != -1) {
		return 1 << right_one_idx;
	}

	return 0;
}

//TEST(BitTest, RightOneTest) {
//	// 仅测试>=0的整数
//    cout << "right one test start\n";
//	int test_times = 500000;
//	int min_val = -100;
//	int max_val = 200;
//	int max_n = 30;
//	for (int i = 0; i < test_times; i++) {
//		int val = RandomVal(0,  numeric_limits<int>::max());
//		if (GetRightOne(val) != test(val)) {
//			cout << GetRightOne(val) << endl;
//			cout << test(val) << endl;
//			ASSERT_TRUE(false);
//		}
//	}
//
//    cout << "test success\n";
//    cout << "right one test end\n\n";
//}