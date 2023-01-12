#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "list_tools.h"
#include "common.h"

using namespace std;
using namespace tools;

/*
 * 输入链表头节点，奇数长度返回中点，偶数长度返回上中点
 */
static ListNode* midOrUpMidNode(ListNode* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return head;
    }

    ListNode* slow = head->next;
    ListNode* fast = head->next->next;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

static ListNode* midOrUpMidNodeTest(ListNode* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return head;
    }

    vector<ListNode*> nodes;
    while (head != nullptr) {
        nodes.push_back(head);
        head = head->next;
    }

    return nodes[(nodes.size() - 1)/ 2];
}

/*
 * 输入链表头节点，奇数长度返回中点，偶数长度返回下中点
 */
static ListNode* midOrDownMidNode(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* slow = head->next;
    ListNode* fast = head->next;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

static ListNode* midOrDownMidNodeTest(ListNode* head) {
    if (head == nullptr) {
        return head;
    }

    vector<ListNode*> nodes;
    while (head != nullptr) {
        nodes.push_back(head);
        head = head->next;
    }
    return nodes[(nodes.size())/ 2];
}
/*
 *  输入链表头节点，奇数长度返回中点前一个，偶数长度返回上中点前一个
 */
static ListNode* midOrUpMidPreNode(ListNode* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return nullptr;
    }

    ListNode* slow = head;
    ListNode* fast = head->next->next;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

static ListNode* midOrUpMidPreNodeTest(ListNode* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return nullptr;
    }

    vector<ListNode*> nodes;
    while (head != nullptr) {
        nodes.push_back(head);
        head = head->next;
    }
    return nodes[(nodes.size() - 3)/2];
}

/*
 * 输入链表头节点，奇数长度返回中点前一个，偶数长度返回下中点前一个
 */
static ListNode* midOrDownPreNode(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }

    if (head->next->next == nullptr) {
        return head;
    }

    ListNode* slow = head->next;
    ListNode* fast = head->next->next;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

static ListNode* midOrDownPreNodeTest(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }

    if (head->next->next == nullptr) {
        return head;
    }

    vector<ListNode*> nodes;
    while (head != nullptr) {
        nodes.push_back(head);
        head = head->next;
    }

    return nodes[(nodes.size() - 2)/2];
}

//TEST(LinkListTest, LinkedListMidTest) {
//	cout << "linked list mid test start\n";
//    int test_times = 100000;
//    int max_n = 100;
//    int min_val = -100;
//    int max_val = 200;
//
//    for (int i = 0; i < test_times; ++i) {
//        ListNode* head = GenRandomList(max_n, min_val, max_val);
//        ListNode* mid1 = midOrUpMidNode(head);
//        ListNode* mid2 = midOrUpMidNodeTest(head);
//        if (mid1 != mid2) {
//            ASSERT_TRUE(false);
//        }
//        FreeList(head);
//    }
//
//    for (int i = 0; i < test_times; ++i) {
//        ListNode* head = GenRandomList(max_n, min_val, max_val);
//        ListNode* mid1 = midOrDownMidNode(head);
//        ListNode* mid2 = midOrDownMidNodeTest(head);
//        if (mid1 != mid2) {
//            ASSERT_TRUE(false);
//        }
//        FreeList(head);
//    }
//
//    for (int i = 0; i < test_times; ++i) {
//        ListNode* head = GenRandomList(max_n, min_val, max_val);
//        ListNode* mid1 = midOrUpMidPreNode(head);
//        ListNode* mid2 = midOrUpMidPreNodeTest(head);
//        if (mid1 != mid2) {
//            ASSERT_TRUE(false);
//        }
//        FreeList(head);
//    }
//
//    for (int i = 0; i < test_times; ++i) {
//        ListNode* head = GenRandomList(max_n, min_val, max_val);
//        ListNode* mid1 = midOrDownMidNode(head);
//        ListNode* mid2 = midOrDownMidNodeTest(head);
//        if (mid1 != mid2) {
//            ASSERT_TRUE(false);
//        }
//        FreeList(head);
//    }
//
//	cout << "test success\n";
//	cout << "linked list mid test end\n\n";
//}
