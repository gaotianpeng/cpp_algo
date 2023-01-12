#include <iostream>
#include <vector>
#include <stack>
#include "gtest/gtest.h"
#include "list_tools.h"

using namespace std;
using namespace tools;

static ListNode* reverseListNode(ListNode* head) {
    if (head == nullptr) {
        return nullptr;
    }

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

static bool IsPalindromeList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }

    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode* reverse_head = slow->next;
    slow->next = nullptr;

    reverse_head = reverseListNode(reverse_head);
    ListNode* from_head = head;
    ListNode* from_end = reverse_head;

    bool ret = true;
    while (from_head != nullptr && from_end != nullptr) {
        if (from_head->val != from_end->val) {
            ret = false;
            break;
        }
        from_head = from_head->next;
        from_end = from_end->next;
    }

    ListNode* back_half_head = reverseListNode(reverse_head);
    slow->next = back_half_head;

    return ret;
}


static bool IsPalindromeList1(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }

    ListNode* right = head->next;
    ListNode* cur = head;
    while (cur->next != nullptr && cur->next->next != nullptr) {
        right = right->next;
        cur = cur->next->next;
    }

    stack<ListNode*> nodes;
    while (right != nullptr) {
        nodes.push(right);
        right = right->next;
    }

    while (!nodes.empty()) {
        if (nodes.top()->val != head->val) {
            return false;
        }
        nodes.pop();
        head = head->next;
    }

    return true;
}

static bool IsPalindromeListTest(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }

    vector<ListNode*> nodes;
    ListNode* cur = head;
    while (cur != nullptr) {
        nodes.push_back(cur);
        cur = cur->next;
    }

    cur = head;
    int n_list = nodes.size();
    while (cur != nullptr) {
        if (cur->val != nodes[--n_list]->val) {
            return false;
        }
        cur = cur->next;
    }

    return true;
}


//TEST(LinkListTest, IsPalindromeListTest) {
//	cout << "is palindrome list test start\n";
//	int test_times = 100000;
//	int max_n = 100;
//	int min_val = -20;
//	int max_val = 30;
//
//	for (int i = 0; i < test_times; i++) {
//		ListNode* head = GenRandomList(max_n, min_val, max_val);
//        if (IsPalindromeList(head) != IsPalindromeListTest(head)) {
//            EXPECT_TRUE(false);
//        }
//		FreeList(head);
//	}
//
//	for (int i = 0; i < test_times; i++) {
//		ListNode* head = GenRandomList(max_n, min_val, max_val);
//        if (IsPalindromeList1(head) != IsPalindromeListTest(head)) {
//            EXPECT_TRUE(false);
//        }
//		FreeList(head);
//	}
//
//	cout << "test success\n";
//	cout << "is palindrome list test end\n\n";
//}