#include <iostream>
#include <vector>
#include <stack>
#include "random.h"
#include "common.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

/*
    实现一个特殊的栈，在基本功能的基础上，再实现返回栈中最小元素的功能
    1) pop、push、getMin操作的时间复杂度都是 O(1)
	2) 设计的栈类型可以使用现成的栈结构
 */
class MinStack1 {
public:
	void push(int val) {
		if (min_data_.empty()) {
			min_data_.push(val);
		} else if (val <= min_data_.top()) {
			min_data_.push(val);
		}

		data_.push(val);
	}

	int pop() {
		int val = data_.top();
		data_.pop();
		if (val == min_data_.top()) {
			min_data_.pop();
		}

		return val;
	}

	int get_min() {
		return min_data_.top();
	}

	int size() {
		return data_.size();
	}

private:
	stack<int> data_;
	stack<int> min_data_;
};

class MinStack2 {
public:
	void push(int val) {
		if (min_data_.empty()) {
			min_data_.push(val);
		} else if (val < min_data_.top()) {
			min_data_.push(val);
		} else {
			int new_min = min_data_.top();
			min_data_.push(new_min);
		}

		data_.push(val);
	}

	int pop() {
		int val = data_.top();
		data_.pop();
		min_data_.pop();
		return val;
	}

	int get_min() {
		return min_data_.top();
	}

	int size() {
		return data_.size();
	}

private:
	stack<int> data_;
	stack<int> min_data_;
};

//TEST(StackTest, GetMinStackTest) {
//    cout << "get min stack test start\n";
//    int min_val = -20;
//    int max_val = 30;
//    int test_times = 100000;
//	int one_test_num = 1000;
//
//	for (int i = 0; i < test_times; ++i) {
//		MinStack1 stack1;
//		MinStack2 stack2;
//		for (int j = 0; j < one_test_num; ++j) {
//			if (Random::random() < 0.33) {
//				int val = RandomVal(min_val, max_val);
//				stack1.push(val);
//				stack2.push(val);
//			} else if (Random::random() < 0.66) {
//				if (stack1.size() != stack2.size()) {
//					EXPECT_FALSE(true);
//					break;
//				}
//
//				if (stack1.size() > 0) {
//					if (stack1.get_min() != stack2.get_min()) {
//						EXPECT_FALSE(true);
//					}
//				}
//			} else {
//				if (stack1.size() != stack2.size()) {
//					EXPECT_FALSE(true);
//					break;
//				}
//
//				if (stack1.size() > 0) {
//					if (stack1.pop() != stack2.pop()) {
//						EXPECT_FALSE(true);
//					}
//				}
//			}
//		}
//	}
//
//    cout << "test success\n";
//    cout << "get min stack end\n\n";
//}