#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "list_tools.h"

using namespace std;
using namespace tools;

ListDNode* ReverseDoubleList(ListDNode* head) {
	if (head == nullptr) {
		return nullptr;
	}

	ListDNode* prev = nullptr;
	ListDNode* next = nullptr;
	while (head != nullptr) {
		// 保存下一结点
		next = head->next;
		head->next = prev;
		head->prev = next;
		prev = head;
		head = next;
	}

	return prev;
}

TEST(LinkListTest, ReverseDoubleList) {
	cout << "reverse double list test start\n";
	int test_times = 500000;
	int max_n = 100;
	int min_val = -20;
	int max_val = 30;

	for (int i = 0; i < test_times; i++) {
		ListDNode* head = GenRandomDList(max_n, min_val, max_val);
		ListDNode* copy = CopyDList(head);
		ListDNode* reverse = ReverseDoubleList(head);
		if (!IsReverse(copy, reverse)) {
			PrintDList(copy);
			PrintDList(reverse);
			FreeList(copy);
			FreeList(reverse);
			EXPECT_TRUE(false);
			break;
		}
		FreeList(copy);
		FreeList(reverse);
	}

	cout << "test success\n";
	cout << "reverse double list test end\n\n";
}