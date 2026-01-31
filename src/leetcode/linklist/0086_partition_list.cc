#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
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

static ListNode* RandomList(int max_n, int min_val, int max_val) {
    vector<int> out;
    RandomArr(out, max_n, min_val, max_val);
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

static int GetListLen(ListNode* head) {
    int n = 0;
    while (head != nullptr) {
        ++n;
        head = head->next;
    }

    return n;
}
static int GetListK(ListNode* head, int k) {
    int ans = 0;
    while (k > 0) {
        --k;
        head = head->next;
    }

    return head->val;
}

} // namespace

/*
    https://leetcode.cn/problems/partition-list/
    86 分隔链表
    给你一个链表的头节点 head 和一个特定值x，请你对链表进行分隔，使得所有小于x 的节点都出现在 大于或等于 x 的节点之前。
    你应当保留两个分区中每个节点的初始相对位置。

*/
static ListNode* partition(ListNode* head, int x) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode dummy1(0);
    ListNode* prev1 = &dummy1;

    ListNode dummy2(0);
    ListNode* prev2 = &dummy2;

    ListNode* cur = head;
    while (cur != nullptr) {
        if (cur->val < x) {
            prev1->next = cur;
            prev1 = prev1->next;
        } else {
            prev2->next = cur;
            prev2 = prev2->next;
        }

        cur = cur->next;
    }
    prev1->next = dummy2.next;
    prev2->next = nullptr;

    return dummy1.next;
}

static ListNode* test(ListNode* head, int x) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    vector<ListNode*> small;
    vector<ListNode*> bigger;
    ListNode* cur = head;
    while (cur != nullptr) {
        if (cur->val < x) {
            small.emplace_back(cur);
        } else {
            bigger.emplace_back(cur);
        }
        cur = cur->next;
    }

    if (small.empty() || bigger.empty()) {
        return head;
    }

    for (int i = 1; i < small.size(); ++i) {
        small[i-1]->next = small[i];
    }

    small[small.size() - 1]->next = bigger[0];
    
    for (int i = 1; i < bigger.size(); ++i) {
        bigger[i-1]->next = bigger[i];
    }
    bigger[bigger.size() - 1]->next = nullptr;

    return small[0];
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;

    int max = 100;
    int min = -100;
    int max_n = 20;
    int test_times = 10000;
    
    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomList(max_n, min, max);
        ListNode* head2 = CopyList(head1);
        int k = Random::nextInt(min, max);
        ListNode* ans1 = partition(head1, k);
        ListNode* ans2 = test(head2, k);

        if (!IsEqual(ans1, ans2)) {
            cout << " test failed " << endl;
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