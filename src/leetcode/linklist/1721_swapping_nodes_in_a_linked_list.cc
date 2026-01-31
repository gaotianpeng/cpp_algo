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

static int GetListLen(ListNode* head) {
    if (head == nullptr) {
        return 0;
    }

    int ans = 0;
    while (head != nullptr) {
        ++ans;
        head = head->next;
    }

    return ans;
}

} // namespace

/*
    https://leetcode.cn/problems/swapping-nodes-in-a-linked-list/
    1721. 交换链表中的节点
        给你链表的头节点head和一个整数k 
        交换 链表正数第k个节点和倒数第k个节点的值后，返回链表的头节点（链表从1开始索引）。
*/

static ListNode* swapNodes(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* fast = head;
    for(int i = 1 ; i < k ; i++){
        fast = fast->next;
    }

    ListNode* kth_node = fast;
    ListNode* slow = head;
    while (fast->next != nullptr) { 
        fast = fast->next;
        slow = slow->next;
    }

    swap(slow->val, kth_node->val);

    return head;
}

static ListNode* test(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* cur = head;
    vector<ListNode*> nodes;
    while (cur != nullptr) {
        nodes.emplace_back(cur);
        cur = cur->next;
    }

    int n = nodes.size();

    ListNode* tmp = nodes[k-1];
    nodes[k - 1] = nodes[n - k];
    nodes[n - k] = tmp;
    for (int i = 1; i < n; ++i) {
        nodes[i-1]->next = nodes[i];
    }
    nodes[n-1]->next = nullptr;

    return nodes[0];
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 10000;
    int min = -10000;
    int max_n = 20;
    int test_times = 50000;


    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomList(max_n, min, max);
        ListNode* head2 = CopyList(head1);

        if (head1 == nullptr) {
            continue;
        }

        int n = GetListLen(head1);
        int k = Random::nextInt(1, n);

        ListNode* ans1 = swapNodes(head1, k);
        ListNode* ans2 = test(head2, k);
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