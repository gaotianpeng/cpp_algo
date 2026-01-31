#include <algorithm>
#include <deque>
#include <iostream>
#include <stack>
#include <vector>
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
    https://leetcode.cn/problems/remove-nodes-from-linked-list/
    2487 分隔链表
        给你一个链表的头节点 head 。
        对于列表中的每个节点 node ，如果其右侧存在一个具有 严格更大 值的节点，则移除 node 。
        返回修改后链表的头节点 head 。
*/

static ListNode* test(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    deque<ListNode*> nodes;
    ListNode* cur = head;
    while (cur != nullptr) {
        nodes.push_front(cur);
        cur = cur->next;
    }

    deque<ListNode*> ans;
    ans.push_back(nodes.front());
    nodes.pop_front();

    while (!nodes.empty()) {
        ListNode* tail = nodes.front();
        nodes.pop_front();
        ListNode* cur_ans = ans.back();
        if (tail->val >= cur_ans->val) {
            ans.push_back(tail);
        } else {
            delete tail;
        }
    }

    ListNode dummy(0);
    ListNode* prev = &dummy;
    while (!ans.empty()) {
        ListNode* node = ans.back();
        ans.pop_back();
        prev->next = node;
        prev = prev->next;
    }
    prev->next = nullptr;

    return dummy.next;
}

static ListNode* removeNodes(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* cur = head->next;
    deque<ListNode*> nodes;
    nodes.push_back(head);

    ListNode dummy(0);
    ListNode* prev = &dummy;

    while (cur != nullptr) {
        while (!nodes.empty()) {
            ListNode* node = nodes.back();
            if (node->val < cur->val) {
                nodes.pop_back();
                delete node;
            }
            else {
                break;
            }
        }
        nodes.push_back(cur);
        cur = cur->next;
    }

    while (!nodes.empty()) {
        prev->next = nodes.front();
        prev = prev->next;
        nodes.pop_front();
    }
    prev->next = nullptr;

    return dummy.next;
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

        ListNode* ans1 = removeNodes(head1);
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

    /*
        输入：head = [5,2,13,3,8]
        输出：[13,8]
    */
    // ListNode * head = new ListNode(5);
	// head->next = new ListNode(2);
	// head->next->next = new ListNode(13);
	// head->next->next->next = new ListNode(3);
    // head->next->next->next->next = new ListNode(8);
    //

    cout << "test end" << endl;
    return 0;
}