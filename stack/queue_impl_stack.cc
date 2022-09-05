#include <iostream>
#include <stack>
#include <queue>
#include "common.h"
#include "random.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

class StackImplQueue {
public:
	void push(int val) {
		push_to_pop();
		stack_push_.push(val);
	}

	int pop() {
		push_to_pop();
		int ret = stack_pop_.top();
		stack_pop_.pop();
		return ret;
	}

	int peek() {
		push_to_pop();
		return stack_pop_.top();
	}

	int size() {
		return stack_push_.size() + stack_pop_.size();
	}

private:
	void push_to_pop() {
		if (stack_pop_.empty()) {
			while (!stack_push_.empty()) {
				stack_pop_.push(stack_push_.top());
				stack_push_.pop();
			}
		}
	}

private:
	stack<int> stack_push_;
	stack<int> stack_pop_;
};

//TEST(StackTest, QueueImplStack) {
//	cout << "queue impl stack test start\n";
//	int min_val = -20;
//	int max_val = 30;
//	int test_times = 100000;
//	int one_test_num = 1000;
//
//	for (int i = 0; i < test_times; ++i) {
//		StackImplQueue queue1;
//		queue<int> queue2;
//		for (int j = 0; j < one_test_num; ++j) {
//			if (Random::random() < 0.33) {
//				int val = RandomVal(min_val, max_val);
//				queue1.push(val);
//				queue2.push(val);
//			} else if (Random::random() < 0.66) {
//				if (queue1.size() != queue2.size()) {
//					EXPECT_FALSE(true);
//					break;
//				}
//				if (queue1.size() > 0) {
//					if (queue1.pop() != queue2.front()) {
//						EXPECT_FALSE(true);
//						break;
//					}
//					queue2.pop();
//				}
//			} else {
//				if (queue1.size() != queue2.size()) {
//					EXPECT_FALSE(true);
//					break;
//				}
//				if (queue1.size() > 0) {
//					if (queue1.peek() != queue2.front()) {
//						EXPECT_FALSE(true);
//						break;
//					}
//				}
//			}
//		}
//	}
//
//	cout << "test success\n";
//	cout << "queue impl stack test end\n";
//}