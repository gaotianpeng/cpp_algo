#include "list_tools.h"
#include "arr_tools.h"
#include "random.h"
#include "common.h"
#include <vector>
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace tools {

ListNode* GenRandomList(int max_n, int min_val, int max_val) {
	vector<int> values;
	RandomArr(values, max_n, min_val, max_val);

	size_t n = values.size();
	if ( n <= 0) {
		return nullptr;
	}

	ListNode* head = new ListNode((int)(Random::random() * (max_val - min_val)) + min_val);
	ListNode* prev = head;
	for (int i = 0; i < n; i++) {
		int val = (int)(Random::random() * (max_val - min_val)) + min_val;
		prev->next = new ListNode(val);
		prev = prev->next;
	}
	prev->next = nullptr;

	return head;
}

ListNode* CopyList(ListNode* src) {
	if (src == nullptr) {
		return nullptr;
	}

	ListNode* ret = new ListNode(src->val);
	ListNode* node = ret;
	src = src->next;
	while (src != nullptr) {
		node->next = new ListNode(src->val);
		src = src->next;
		node = node->next;
	}
	node->next = nullptr;

	return ret;
}

void FreeList(ListNode* list) {
	if (list == nullptr) {
		return;
	}

	while (list != nullptr) {
		ListNode* next = list->next;
		delete list;
		list = next;
	}
}

void PrintList(ListNode* list) {
	if (list == nullptr) {
		return;
	}

	ListNode* head = list;
	while (head != nullptr) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}

static void GetListValues(ListNode* list, vector<int>& out) {
	if (list == nullptr) {
		return;
	}

	ListNode* head = list;
	while (head != nullptr) {
		out.emplace_back(head->val);
		head = head->next;
	}
}

bool IsReverse(ListNode* list_a, ListNode* list_b) {
	if (list_a == nullptr && list_b == nullptr) {
		return true;
	}

	if (list_a == nullptr && list_b != nullptr) {
		return false;
	}

	if (list_a != nullptr && list_b == nullptr) {
		return false;
	}

	vector<int> a_values;
	GetListValues(list_a, a_values);
	vector<int> b_values;
	GetListValues(list_b, b_values);
	return IsReverse(a_values, b_values);
}

ListDNode* GenRandomDList(int max_n, int min_val, int max_val) {
	vector<int> values;
	RandomArr(values, max_n, min_val, max_val);

	size_t n = values.size();
	if ( n <= 0) {
		return nullptr;
	}

	ListDNode* head = new ListDNode(RandomVal(min_val, max_val));
	ListDNode* ret = head;

	ListDNode* prev = nullptr;
	for (size_t i = 1; i < n; i++) {
		prev = head;
		head = new ListDNode(RandomVal(min_val, max_val));
		prev->next = head;
		head->prev = prev;
		head->next = nullptr;
	}

	return ret;
}

ListDNode* CopyDList(ListDNode* dlist) {
	if (dlist == nullptr) {
		return nullptr;
	}

	ListDNode* ret = new ListDNode(dlist->val);
	ret->next = dlist->next;
	ret->prev = nullptr;

	dlist = dlist->next;

	ListDNode* prev = ret;

	while (dlist != nullptr) {
		ListDNode* node = new ListDNode(dlist->val);
		prev->next = node;
		node->prev = prev;
		prev = node;
		dlist = dlist->next;
	}

	return ret;
}

bool IsReverse(ListDNode* list_a, ListDNode* list_b) {
	if (list_a == nullptr && list_b == nullptr) {
		return true;
	}

	if (list_a != nullptr && list_b == nullptr) {
		return false;
	}

	if (list_a == nullptr&& list_b != nullptr) {
		return false;
	}

	vector<int> vec_a;
	vector<int> vec_b;
	while (list_a != nullptr) {
		vec_a.emplace_back(list_a->val);
		list_a = list_a->next;
	}

	while (list_b != nullptr) {
		vec_b.emplace_back(list_b->val);
		list_b = list_b->next;
	}

	if (vec_a.size() != vec_b.size()) {
		return false;
	}

	size_t n = vec_a.size();
	for (int i = 0; i < n; i++) {
		if (vec_a[i] != vec_b[n-1-i]) {
			return false;
		}
	}

	return true;
}

void PrintDList(ListDNode* list) {
	while (list != nullptr) {
		cout << list->val << " ";
		list = list->next;
	}

	cout << endl;
}

void FreeList(ListDNode* list) {
	ListDNode* next = nullptr;
	while (list != nullptr) {
		next = list->next;
		delete list;
		list = next;
	}
}

} // namespace tools

//using namespace tools;
//
//TEST(ListTool, ListToolTest) {
//	int min_val = -10;
//	int max_val = 10;
//	int max_n = 10;
//	int test_times = 100;
//	for (int i = 0; i < test_times; ++i) {
//		ListDNode* d_list = GenRandomDList(max_n, min_val, max_val);
//		ListDNode* copy_list = CopyDList(d_list);
//		if (IsReverse(d_list, copy_list)) {
//			PrintDList(d_list);
//			PrintDList(copy_list);
//		}
//		FreeList(d_list);
//		FreeList(copy_list);
//	}
//};
