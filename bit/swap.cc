#include <iostream>
#include <limits>
#include "gtest/gtest.h"
#include "common.h"

using namespace std;
using namespace tools;

static void swap(int& a, int& b) {
	a = a^b;
	b = a^b;
	a = a^b;
}

static void test(int& a, int&b) {
	int tmp = a;
	b = a;
	a = tmp;
}

//TEST(BitTest, SwapTest) {
//    cout << "swap test start\n";
//    int max_n = 100;
//    int min_val = std::numeric_limits<int>::min();
//    int max_val = std::numeric_limits<int>::max();
//
//    int test_times = 100000;
//    for (int i = 0; i < test_times; i++) {
//		int a1 = RandomVal(min_val, max_val);
//		int b1 = RandomVal(min_val, max_val);
//
//		int a2 = a1;
//		int b2 = b1;
//		swap(a1, b1);
//		test(a2, b2);
//		if ((a1 != a2) || (a2 != b2)) {
//			EXPECT_TRUE(false);
//			break;
//		}
//    }
//    cout << "test success\n";
//    cout << "swap sort end\n\n";
//}