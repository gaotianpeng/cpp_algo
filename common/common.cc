#include "common.h"
#include "random.h"
#include <iostream>
#include <numeric>
#include "gtest/gtest.h"

using namespace std;

namespace tools {

void Swap(int& a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int RandomVal(int min_val, int max_val) {
	return Random::random(min_val, max_val);
}

int RandomOddVal(int min_val, int max_val) {
	int ret = Random::random(min_val, max_val);
	while ((ret & 1) == 0) {
		ret = Random::random(min_val, max_val);
	}
	return ret;
}

int RandomEvenVal(int min_val, int max_val) {
	int ret = Random::random(min_val, max_val);
	while ((ret & 1) != 0) {
		ret = Random::random(min_val, max_val);
	}
	return ret;
}

// TEST(CommonTest, RandomOddTest) {
// 	cout << "random odd test start\n";
// 	int min_val = numeric_limits<int>::min();
// 	int max_val = numeric_limits<int>::max();
// 	int test_times = 100000;
// 	for (int i = 0; i < test_times; i++) {
// 		int val = RandomOddVal(min_val, max_val);
// 		if (!(val % 2 == 1) && !(val % 2 == -1)) {
// 			cout << val << endl;
// 			ASSERT_TRUE((false));
// 		}
// 	}

// 	cout << "test success\n";
// 	cout << "random odd test end\n\n";
// }

//TEST(CommonTest, RandomEvenTest) {
//	cout << "random even test start\n";
//	int min_val = numeric_limits<int>::min();
//	int max_val = numeric_limits<int>::max();
//	int test_times = 100000;
//	for (int i = 0; i < test_times; i++) {
//	    int val = RandomEvenVal(min_val, max_val);
//	    if (!(val % 2 == 0)) {
//	        cout << val << endl;
//	        ASSERT_TRUE((false));
//	    }
//	}
//
//	cout << "test success\n";
//	cout << "random even test end\n\n";
//}

} // namespace tools