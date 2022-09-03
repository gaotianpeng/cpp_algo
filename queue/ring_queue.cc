#include <iostream>
#include <vector>
#include <exception>
#include "gtest/gtest.h"

using namespace std;

class RingQueue {
public:
	RingQueue(int limit):limit_(limit) {
		arr_ = new int[limit];
		poll_idx_ = 0;
		push_idx_ = 0;
		size_ = 0;
	}

	~RingQueue() {
		delete[] arr_;
	}

	bool push(int val) {
		if (size_ == limit_) {
			return false;
		}

		size_++;
		arr_[push_idx_] = val;
		push_idx_ = nextIndex(push_idx_);

		return true;
	}

	int pop() {
		if (size_ == 0) {
			throw;
		}

		--size_;
		int ans = arr_[poll_idx_];
		poll_idx_ = nextIndex(poll_idx_);
		return ans;
	}

	bool empty() {
		return size_ == 0;
	}

protected:
	int nextIndex(int i) {
		return i < limit_ - 1 ? i + 1: 0;
	}

private:
	int* arr_;
	int size_;
	int limit_;
	int push_idx_;
	int poll_idx_;
};

