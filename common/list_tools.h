#ifndef CPP_ALGO_COMMON_LIST_TOOLS_H_
#define CPP_ALGO_COMMON_LIST_TOOLS_H_

namespace tools {

struct ListNode {
	int val;
	ListNode* next = nullptr;
	ListNode(int v) {
		val = v;
	}
};

ListNode* GenRandomList(int max_n, int min_val, int max_val);

ListNode* CopyList(ListNode* src);

void FreeList(ListNode* list);

void PrintList(ListNode* list);

bool IsReverse(ListNode* list_a, ListNode* list_b);

} // namespace tools

#endif //CPP_ALGO_COMMON_LIST_TOOLS_H_
