#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "list_tools.h"

using namespace std;
using namespace tools;

ListNode* ReverseList(ListNode* head) {
	if (head == nullptr) {
		return nullptr;
	}

	ListNode* prev = nullptr;
	ListNode* next = nullptr;
	while (head != nullptr) {
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}

	return prev;
}

TEST(LinkListTest, ReverseList) {
	cout << "reverse list test start\n";
	int test_times = 500000;
	int max_n = 100;
	int min_val = -20;
	int max_val = 30;

	for (int i = 0; i < test_times; i++) {
		ListNode* head = GenRandomList(max_n, min_val, max_val);
		ListNode* copy = CopyList(head);
		ListNode* reverse = ReverseList(head);
		if (!IsReverse(copy, reverse)) {
			PrintList(copy);
			PrintList(reverse);
			FreeList(copy);
			FreeList(reverse);
			EXPECT_TRUE(false);
			break;
		}
		FreeList(copy);
		FreeList(reverse);
	}

	cout << "test success\n";
	cout << "reverse list test end\n\n";
}