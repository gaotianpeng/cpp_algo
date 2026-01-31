#include <iostream>
#include <vector>
#include <algorithm>
#include "common/test_utils.h"

using namespace std;
using namespace test_utils;

/*
    for test
*/
namespace {

// Custom RandomArr function
static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Random::nextDouble() * max_n);
	for (int i = 0; i < len; i++) {
		int val = Random::nextInt(min_val, max_val);
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
    https://leetcode.cn/problems/merge-two-sorted-lists/
    21 合并两个有序链表
        将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的
*/
static ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr) {
        return list2;
    }

    if (list2 == nullptr) {
        return list1;
    }

    ListNode* ans = list1->val < list2->val ? list1: list2;
    if (ans == list1) {
        list1 = list1->next;
    } else {
        list2 = list2->next;
    }

    ListNode* pre = ans;

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val <= list2->val) {
            pre->next = list1;
            list1 = list1->next;
        } else {
            pre->next = list2;
            list2 = list2->next;
        }

        pre = pre->next;
    }

    pre->next = list1 != nullptr ? list1 : list2;

    return ans;
}

static ListNode* mergeTwoLists1(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr) {
        return list2;
    }

    if (list2 == nullptr) {
        return list1;
    }

    ListNode dummy(0);
    ListNode* pre = &dummy;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val <= list2->val) {
            pre->next = list1;
            list1 = list1->next;
        } else {
            pre->next = list2;
            list2 = list2->next;
        }
        pre = pre->next;
    }

    while (list1 != nullptr) {
        pre->next = list1;
        pre = pre->next;
        list1 = list1->next;
    }

    while (list2 != nullptr) {
        pre->next = list2;
        pre = pre->next;
        list2 = list2->next;
    }

    return dummy.next;
}

static ListNode* test(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr) {
        return list2;
    }

    if (list2 == nullptr) {
        return list1;
    }

    vector<ListNode*> nodes;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val <= list2->val) {
            nodes.emplace_back(list1);
            list1 = list1->next;
        } else {
            nodes.emplace_back(list2);
            list2 = list2->next;
        }
    }

    while (list1 != nullptr) {
        nodes.emplace_back(list1);
        list1 = list1->next;
    }

    while (list2 != nullptr) {
        nodes.emplace_back(list2);
        list2 = list2->next;
    }

    for (int i = 1; i < nodes.size(); ++i) {
        nodes[i-1]->next = nodes[i];
    }
    nodes[nodes.size() - 1]->next = nullptr;

    return nodes[0];
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 10;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomSortedList(max_n, min, max);
        ListNode* head2 = RandomSortedList(max_n, min, max);
        ListNode* head12 = CopyList(head1);
        ListNode* head22 = CopyList(head2);
        ListNode* head13 = CopyList(head1);
        ListNode* head23 = CopyList(head2);
 
        ListNode* ans1 = mergeTwoLists(head1, head2);
        ListNode* ans2 = test(head12, head22);
        ListNode* ans3 = mergeTwoLists1(head13, head23);
        if (!IsEqual(ans1, ans2) || !IsEqual(ans2, ans2)) {
            cout << "test failed" << endl;
            FreeList(ans1);
            FreeList(ans2);
            FreeList(ans3);
            break;
        }


        FreeList(ans1);
        FreeList(ans2);
        FreeList(ans3);
    }

    cout << "test end" << endl;

    return 0;
}