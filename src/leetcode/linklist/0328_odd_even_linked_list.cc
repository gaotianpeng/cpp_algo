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

} // namespace

/*
    https://leetcode.cn/problems/odd-even-linked-list/
    328 奇偶链表
        给定单链表的头节点 head ，将所有索引为奇数的节点和索引为偶数的节点分别组合在一起，然后返回重新排序的列表
        第一个节点的索引被认为是 奇数 ， 第二个节点的索引为 偶数 ，以此类推

        示例
            输入: head = [1,2,3,4,5]
            输出: [1,3,5,2,4]
*/
static ListNode* oddEvenList(ListNode* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return head;
    }

    ListNode* evenHead = head->next;
    ListNode* odd = head;
    ListNode* even = evenHead;

    while (even != nullptr && even->next != nullptr) {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    odd->next = evenHead;

    return head;
}

static ListNode* test(ListNode* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return head;
    }

    ListNode* even_head = head->next;
    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* cur = head->next->next;
    bool odd_sign = true;

    while (cur != nullptr) {
        if (odd_sign) {
            odd->next = cur;
            odd = odd->next;
            
        } else {
            even->next = cur;
            even = even->next;
        }
        
        odd_sign = !odd_sign;
        cur = cur->next;
    }
    even->next = nullptr;
    odd->next = even_head;

    return head;
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 10000;
    int min = -10000;
    int max_n = 5;
    int test_times = 50000;

    bool sign = true;

    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomList(max_n, min, max);
        ListNode* head2 = CopyList(head1);

        ListNode* list1 = oddEvenList(head1);
        ListNode* list2 = test(head2);
        if (!IsEqual(list1, list2)) {
            cout << "test failed" << endl;
            PrintList(list1);
            PrintList(list2);
            FreeList(head1);
            FreeList(head2);

            break;
        }

        FreeList(head1);
        FreeList(head2);
    }

    cout << "test end" << endl;

    return 0;
}