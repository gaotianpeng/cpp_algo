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

} // namespace

/*
    https://leetcode.cn/problems/add-two-numbers-ii/
    445. 两数相加 II
    给你两个 非空 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。
    将这两数相加会返回一个新的链表。
    你可以假设除了数字 0 之外，这两个数字都不会以零开头。
*/
static ListNode* reverse(ListNode* head){
    ListNode* pre = nullptr;
    ListNode* next = nullptr;

    while (head != nullptr) {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }

    return pre;
}

static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) {
        return l2;
    }
    if (l2 == nullptr) {
        return l1;
    }

    ListNode* rev1 = reverse(l1);
    ListNode* rev2 = reverse(l2);

    ListNode* cur1 = rev1;
    ListNode* cur2 = rev2;
    int carry = 0;
    ListNode dummy(0);
    ListNode* pre = &dummy;


    while (cur1 != nullptr && cur2 != nullptr) {
        ListNode* cur = new ListNode((cur1->val + cur2->val +carry) % 10);
        carry = (cur1->val + cur2->val +carry) / 10;
        pre->next = cur;
        pre = pre->next;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    ListNode* cur = cur1 == nullptr ? cur2 : cur1;
    while (cur != nullptr) {
        ListNode* temp = new ListNode((cur->val + carry) % 10);
        carry = (cur->val + carry) / 10;
        pre->next = temp;
        pre = pre->next;
        cur = cur->next;
    }

    if (carry != 0) {
        pre->next = new ListNode(carry);
    }

    // 恢复现场
    reverse(rev1);
    reverse(rev2);

    return reverse(dummy.next);
}

ListNode* test(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) {
        return l2;
    }

    if (l2 == nullptr) {
        return l1;
    }

    deque<ListNode*> nodes1;
    deque<ListNode*> nodes2;
    ListNode* cur = l1;
    while (cur != nullptr) {
        nodes1.emplace_back(cur);
        cur = cur->next;
    }
    
    cur = l2;
    while (cur != nullptr) {
        nodes2.emplace_back(cur);
        cur = cur->next;
    }

    int carry = 0;
    ListNode dummy(0);
    ListNode* prev = &dummy;
    while (!nodes1.empty() && !nodes2.empty()) {
        ListNode* tmp_node1 = nodes1.back();
        ListNode* tmp_node2 = nodes2.back();
        nodes1.pop_back();
        nodes2.pop_back();
        cur = new ListNode((tmp_node1->val + tmp_node2->val + carry) % 10);
        carry = (tmp_node1->val + tmp_node2->val + carry) / 10;
        prev->next = cur;
        prev = prev->next;
    }

    while (!nodes1.empty()) {
        ListNode* tmp_node = nodes1.back();
        nodes1.pop_back();
        cur = new ListNode((tmp_node->val + carry) % 10);
        carry = (tmp_node->val + carry) / 10;
        prev->next = cur;
        prev = prev->next;
    }

    while (!nodes2.empty()) {
        ListNode* tmp_node = nodes2.back();
        nodes2.pop_back();
        cur = new ListNode((tmp_node->val + carry) % 10);
        carry = (tmp_node->val + carry) / 10;
        prev->next = cur;
        prev = prev->next;
    }

    if (carry != 0) {
        prev->next = new ListNode(carry);
    }

    return reverse(dummy.next);
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;

    int max = 9;
    int min = 0;
    int max_n = 10;
    int test_times = 10000;
    
    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomList(max_n, min, max);
        ListNode* head2 = RandomList(max_n, min, max);
        ListNode* ans1 = addTwoNumbers(head1, head2);
        ListNode* ans2 = test(head1, head2);
        if (!IsEqual(ans1, ans2)) {
            PrintList(head1);
            PrintList(head2);
            PrintList(ans1);
            PrintList(ans2);
            cout << "test failed" << endl;
            if (ans1 != ans2) {
                FreeList(ans1);
                FreeList(ans2);
            }

            FreeList(head1);
            FreeList(head2);
            break;
        }

        if (ans1 != ans2) {
            FreeList(ans1);
            FreeList(ans2);
        }

        FreeList(head1);
        FreeList(head2);
    }

    cout << "test end" << endl;
    return 0;
}