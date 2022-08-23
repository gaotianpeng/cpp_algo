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

} // namespace tools
