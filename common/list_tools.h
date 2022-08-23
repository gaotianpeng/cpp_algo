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

void FreeList(ListNode* list);

void PrintList(ListNode* list);

} // namespace tools

#endif //CPP_ALGO_COMMON_LIST_TOOLS_H_
