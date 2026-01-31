#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

/*
    for test
*/
namespace {

static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Random::nextDouble() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(Random::nextDouble() * (max_val - min_val + 1)) + min_val;
		out.emplace_back(val);
	}
}

struct ListNode{
    int val  = 0;
    ListNode* next = nullptr;

    ListNode(int v):val(v) {
    }
};

static ListNode* RandomSortedList(int max_n, int min_val, int max_val) {
    vector<int> out;
    RandomArr(out, max_n, min_val, max_val);
    std::sort(out.begin(), out.end());
    vector<ListNode*> lists;
    for (auto& elem: out) {
        lists.emplace_back(new ListNode(elem));
    }

    if (lists.size() == 0) {
        return nullptr;
    }

    for (int i = 1; i < lists.size(); ++i) {
        lists[i-1]->next = lists[i];
    }
    lists[lists.size() - 1]->next = nullptr;
    return lists[0];
}

static ListNode* CopyList(ListNode* head) {
    if (head == nullptr) {
        return nullptr;
    }

    ListNode* ans = new ListNode(head->val);
    ListNode* ans_head = ans;
    while (head->next != nullptr) {
        ans->next = new ListNode(head->next->val);
        ans = ans->next;
        head = head->next;
    }
    return ans_head;
}

static void PrintList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

static bool IsEqual(ListNode* head1, ListNode* head2) {
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->val != head2->val) {
            return false;
        }
        head1 = head1->next;
        head2 = head2->next;
    }

    if (head1 != nullptr || head2 != nullptr) {
        return false;
    }
    return true;
}

static void FreeList(ListNode* head) {
    while (head != nullptr) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

} // namespace

/*
    https://leetcode.cn/problems/insertion-sort-list/
    0147 对链表进行插入排序
        给定单个链表的头 head ，使用 插入排序 对链表进行排序，并返回 排序后链表的头
*/
static ListNode* insertNode(ListNode* list, ListNode* node) {
    if (list == nullptr || node == nullptr) {
        return list;
    }

    ListNode* pre = nullptr;
    ListNode* cur = list;
    while (cur != nullptr) {
        if (cur->val > node->val) {
            break;
        }
        pre = cur;
        cur = cur->next;
    }

    if (pre == nullptr) {
        node->next = list;
        return node;
    } else {
        node->next = pre->next;
        pre->next = node;
        return list;
    }
}

static ListNode* insertionSortList(ListNode* list) {
    if (list == nullptr || list->next == nullptr) {
        return list;
    }

    ListNode* ans = list;
    ListNode* next = ans->next;
    ans->next = nullptr;
    while (next != nullptr) {
        ListNode* next_next = next->next;
        ans = insertNode(ans, next);
        next = next_next;
    }

    return ans;
}


struct Comp {
    bool operator() (std::pair<int, ListNode*> a, std::pair<int, ListNode*> b) {
        return a.first > b.first;
    }
};

static ListNode* test(ListNode* list) {
    if (list == nullptr || list->next == nullptr) {
        return list;
    }

    priority_queue<std::pair<int, ListNode*>, 
        vector<std::pair<int, ListNode*>>, Comp> queue;

    while (list != nullptr) {
        queue.push(std::make_pair(list->val, list));
        list = list->next;
    }

    ListNode* ans = queue.top().second;
    ListNode* pre = ans;
    queue.pop();

    while (!queue.empty()) {
        pre->next = queue.top().second;
        queue.pop();
        pre = pre->next;
    }

    pre->next = nullptr;

    return ans;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 10;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomSortedList(max_n, min, max);
        ListNode* head2 = CopyList(head1);
        ListNode* ans1 = insertionSortList(head1);
        ListNode* ans2 = test(head2);
        
        if (!IsEqual(ans1, ans2)) {
            cout << "test failed" << endl;
            FreeList(ans1);
            FreeList(ans2);
            break;
        }

        FreeList(ans1);
        FreeList(ans2);
    }

    cout << "test end" << endl;

    return 0;
}