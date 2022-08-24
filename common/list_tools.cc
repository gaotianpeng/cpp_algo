#include "list_tools.h"
#include "arr_tools.h"
#include "random.h"
#include <vector>
#include <iostream>

using namespace std;

namespace tools {

ListNode* GenRandomList(int max_n, int min_val, int max_val) {
	vector<int> values;
	RandomArr(values, max_n, min_val, max_val);

	size_t n = values.size();
	if ( n <= 0) {
		return nullptr;
	}

	Random random;
	ListNode* head = new ListNode((int)(random() * (max_val - min_val)) + min_val);
	ListNode* prev = head;
	for (int i = 0; i < n; i++) {
		int val = (int)(random() * (max_val - min_val)) + min_val;
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

} // namespace tools
