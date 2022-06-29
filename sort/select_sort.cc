#include <iostream>
#include "random.h"
#include "gtest/gtest.h"

using namespace std;

TEST(Random, RandomTest) {
	Random random;
	for (int j = 0; j < 100000; j++) {
		int less = 0;
		int more = 0;
		for (int i = 0; i < 10000; i++) {
			if (random() <= 0.5) {
                less++;
            } else {
                more++;
            }
		}
		EXPECT_TRUE((more - less) < 1000);
	}
}