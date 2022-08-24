#include "random.h"
#include "gtest/gtest.h"
#include <iostream>
using namespace std;

namespace tools {

std::random_device Random::r;
std::mt19937 Random::eng = SeededEng();

} // namespace tools

//TEST(RandomTest, Random) {
//	int test_times = 100000000;
//	int lower = 0;
//	int mid = 0;
//	int high = 0;
//	for (int i = 0; i < test_times; i++) {
//		double val = tools::Random::random();
//		if (val < 0.33333) {
//			++lower;
//		} else if (val < 0.66666) {
//			++mid;
//		} else {
//			++high;
//		}
//	}
//
//	cout << lower << ", " << mid <<", " << high << endl;
//}

