#include <iostream>
#include <vector>
#include <exception>
#include <deque>
#include "common.h"
#include "random.h"

#include "gtest/gtest.h"

using namespace std;
using namespace tools;

namespace {

struct Node {
	int val;
	Node *last;
	Node *next;

	Node(int v) {
		val = v;
		last = nullptr;
		next = nullptr;
	}
};

class DoubleEndQueue {
	public:
	~DoubleEndQueue() {
		while (head_ != nullptr) {
			Node *cur = head_;
			head_ = head_->next;
			delete cur;
			cur = nullptr;
		}
	}

	void AddFromHead(int val) {
		Node *cur = new Node(val);
		if (head_ == nullptr) {
			head_ = cur;
			tail_ = cur;
		} else {
			cur->next = head_;
			head_->last = cur;
			head_ = cur;
		}
	}

	void AddFromTail(int val) {
		Node *cur = new Node(val);
		if (head_ == nullptr) {
			head_ = cur;
			tail_ = cur;
		} else {
			tail_->next = cur;
			cur->last = tail_;
			tail_ = cur;
		}
	}

	int PopFromHead() {
		if (head_ == nullptr) {
			throw;
		}

		int ret = head_->val;
		Node *cur = head_;
		if (head_ == tail_) {
			tail_ = nullptr;
			head_ = nullptr;
		} else {
			head_ = head_->next;
			head_->last = nullptr;
		}
		delete cur;

		return ret;
	}

	int PopFromTail() {
		if (head_ == nullptr) {
			throw;
		}

		int ret = tail_->val;
		Node *cur = tail_;
		if (head_ == tail_) {
			head_ = nullptr;
			tail_ = nullptr;
		} else {
			tail_ = tail_->last;
			tail_->next = nullptr;
		}
		delete cur;
		cur = nullptr;

		return ret;
	}

	bool IsEmpty() {
		return head_ == tail_;
	}

private:
	Node *head_ = nullptr;
	Node *tail_ = nullptr;
};

}

//TEST(QueueTest, DoubleEndsQueueTest) {
//    cout << "double ends queue  test start\n";
//	int one_time_test_data_num = 100;
//	int test_times = 500000;
//	int min_val = -100;
//	int max_val = 200;
//	for (int i = 0; i < test_times; ++i) {
//		DoubleEndQueue my_queue_;
//		deque<int> que_;
//		for (int j = 0; j < one_time_test_data_num; ++j) {
//			int val = RandomVal(min_val, max_val);
//			if (RandomVal(min_val, max_val) < 0.25) {
//				my_queue_.AddFromHead(val);
//				que_.push_front(val);
//			} else if (RandomVal(min_val, max_val) < 0.50) {
//				if (que_.size() > 0) {
//					int val1 = my_queue_.PopFromHead();
//					int val2 = que_.front();
//					que_.pop_front();
//					if (val1 != val2) {
//						EXPECT_TRUE(false);
//						break;
//					}
//				}
//			} else if (RandomVal(min_val, max_val) < 0.75) {
//				my_queue_.AddFromTail(val);
//				que_.push_back(val);
//			} else {
//				if (que_.size() > 0) {
//					int val1 = my_queue_.PopFromTail();
//					int val2 = que_.back();
//					que_.pop_back();
//					if (val1 != val2) {
//						EXPECT_TRUE(false);
//						break;
//					}
//				}
//			}
//		}
//	}
//	cout << "test success\n";
//	cout << "double ends queue test end\n";
//}