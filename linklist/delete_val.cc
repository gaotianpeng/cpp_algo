#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "list_tools.h"
#include "common.h"

using namespace std;
using namespace tools;

ListNode* DeleteListVal(ListNode* head, int val) {
	if (head == nullptr) {
		return nullptr;
	}

	while (head != nullptr) {
		if (head->val != val) {
			break;
		}
		ListNode* cur = head;
		head = head->next;
		delete cur;
	}

	ListNode* prev = head;
	ListNode* cur = head;

	while (cur != nullptr) {
		if (cur->val != val) {
			prev = cur;
			cur = cur->next;
		} else {
			prev->next = cur->next;
			delete cur;
			cur = prev->next;
		}
	}

	return head;
}

ListNode* test(ListNode* head, int val) {
	if (head == nullptr) {
		return nullptr;
	}

	vector<ListNode*> lists;
	while (head != nullptr) {
		lists.push_back(head);
		head = head->next;
	}

	for (int i = 0; i < lists.size(); ++i) {
		if (lists[i]->val == val) {
			delete lists[i];
			lists[i] = nullptr;
		}
	}

	ListNode* ret = nullptr;
	int ret_pos = 0;
	for (int i = 0; i < lists.size(); ++i) {
		if (lists[i] != nullptr) {
			ret_pos = i;
			break;
		}
	}

	ret = lists[ret_pos];
	ListNode* prev = ret;
	for (int i = ret_pos + 1; i < lists.size(); ++i) {
		if (lists[i] != nullptr) {
			prev->next = lists[i];
			prev = lists[i];
		}
	}
	prev->next = nullptr;

	return ret;
}
//
//TEST(LinkListTest, DeleteValList) {
//	cout << "delete val test start\n";
//	int test_times = 100000;
//	int max_n = 100;
//	int min_val = -20;
//	int max_val = 30;
//
//	for (int i = 0; i < test_times; i++) {
//		ListNode* head = GenRandomList(max_n, min_val, max_val);
//		ListNode* copy = CopyList(head);
//		int val = RandomVal(min_val, max_val);
//		ListNode* list1 = DeleteListVal(head, val);
//		ListNode* list2 = test(copy, val);
//
//		if (!IsEqual(list1, list2)) {
//			PrintList(list1);
//			PrintList(list2);
//			EXPECT_TRUE(false);
//			break;
//		}
//
//		FreeList(list1);
//		FreeList(list2);
//	}
//
//	cout << "test success\n";
//	cout << "delete val test end\n\n";
//}