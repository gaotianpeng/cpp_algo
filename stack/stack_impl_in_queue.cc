#include <iostream>
#include <stack>
#include <queue>
#include "common.h"
#include "random.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tools;

/*
 * 用队列结构实现栈结构
 */
class StackImplInQueue {
public:
	StackImplInQueue() {
		queue_ = new queue<int>();
		help_ = new queue<int>();
	}

	~StackImplInQueue() {
		delete queue_;
		queue_ = nullptr;
		delete help_;
		help_ = nullptr;
	}

	int top() {
		while (queue_->size() > 1) {
			help_->push(queue_->front());
			queue_->pop();
		}

		int ret = queue_->front();
		queue_->pop();
		help_->push(ret);
		queue<int>* tmp = queue_;
		queue_ = help_;
		help_ = tmp;
		return ret;
	}

	int size()  {
		return queue_->size() + help_->size();
	}

	void pop() {
		while (queue_->size() > 1) {
			help_->push(queue_->front());
			queue_->pop();
		}

		queue_->pop();
		queue<int>* tmp = queue_;
		queue_ = help_;
		help_ = tmp;
	}

	void push(int val) {
		queue_->push(val);
	}

	bool empty() {
		return queue_->empty() && help_->empty();
	}

private:
	queue<int> *queue_;
	queue<int> *help_;
};

//TEST(StackTest, StackImplInQueue) {
//	cout << "stack impl in queue test start\n";
//	int min_val = -20;
//	int max_val = 30;
//	int test_times = 100000;
//	int one_test_num = 1000;
//
//	for (int i = 0; i < test_times; ++i) {
//		stack<int> stack1;
//		StackImplInQueue stack2;
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
//				if (stack1.size() > 0) {
//					if (stack1.top() != stack2.top()) {
//						EXPECT_FALSE(true);
//						break;
//					}
//				}
//			} else {
//				if (stack1.size() != stack2.size()) {
//					EXPECT_FALSE(true);
//					break;
//				}
//
//				if (stack1.size() > 0) {
//					stack1.pop();
//					stack2.pop();
//				}
//			}
//		}
//	}
//
//	cout << "test success\n";
//	cout << "stack impl in queue test end\n";
//}