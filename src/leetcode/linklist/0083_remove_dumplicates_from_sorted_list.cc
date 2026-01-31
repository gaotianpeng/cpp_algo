#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

/*
    for test
*/
namespace {

// Custom RandomSortedArr function
static void RandomSortedArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Random::nextDouble() * max_n);
	for (int i = 0; i < len; i++) {
		int val = Random::nextInt(min_val, max_val);
		out.emplace_back(val);
	}
    std::sort(out.begin(), out.end());
}

struct ListNode{
    int val  = 0;
    ListNode* next = nullptr;

    ListNode(int v):val(v) {
    }
};

static ListNode* RandomSortedList(int max_n, int min_val, int max_val) {
    vector<int> out;
    RandomSortedArr(out, max_n, min_val, max_val);
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
    https://leetcode.cn/problems/remove-duplicates-from-sorted-list/
    83. 删除排序链表中的重复元素
        给定一个已排序的链表的头head, 删除所有重复的元素，使每个元素只出现一次 
        返回已排序的链表 
*/
ListNode* deleteDuplicates(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* ans = head;
    ListNode* pre = head;
    ListNode* cur = head->next;
    pre->next = nullptr;

    while (cur != nullptr) {
        if (cur->val == pre->val) {
            ListNode* tmp = cur;
            cur = cur->next;
            delete tmp;
        } else {
            pre->next = cur;
            pre = cur;
            cur = cur->next;
            pre->next = nullptr;
        }
    }

    return ans;
}

ListNode* test(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    } 

    set<int> vals;
    vals.insert(head->val);

    ListNode* pre = head;
    ListNode* cur = head->next;
    pre->next = nullptr;

    while (cur != nullptr) {
        auto iter = vals.find(cur->val);
        if (iter != vals.end()) {
            ListNode* tmp = cur;
            cur = cur->next;
            delete tmp;
        } else {
            vals.insert(cur->val);
            pre->next = cur;
            pre = cur;
            cur = cur->next;
            pre->next = nullptr;
        }
    }
    
    return head;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;

    int max = 100;
    int min = -100;
    int max_n = 20;
    int test_times = 100000;
    
    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomSortedList(max_n, min, max);
        ListNode* head2 = CopyList(head1);

        ListNode* ans1 = deleteDuplicates(head1);
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