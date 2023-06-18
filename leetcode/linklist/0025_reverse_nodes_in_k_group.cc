#include <algorithm>
#include <iostream>
#include <random>
#include <map>
#include <stack>
#include <vector>

using namespace std;

/*
    for test
*/
namespace {

class Math {
public:
    static double random() {
        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_real_distribution<> distribution(0.0, 1.0);
        return distribution(engine);
    }
};

static void RandomSortedArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Math::random() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(Math::random() * (max_val - min_val + 1)) + min_val;
		out.emplace_back(val);
	}
    std::sort(out.begin(), out.end());
}

static int RandomVal(int min_val, int max_val) {
    return (int)(Math::random()*(max_val - min_val)) + min_val;
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
    https://leetcode.cn/problems/reverse-nodes-in-k-group/
    25. K 个一组翻转链表
    给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
    k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
    你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换

*/
static ListNode* reverseList(ListNode* head) {
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

static pair<ListNode*, ListNode*> reverseList(ListNode* head, ListNode* tail) {
    ListNode* prev = tail->next;
    ListNode* p = head;
    while (prev != tail) {
        ListNode* nex = p->next;
        p->next = prev;
        prev = p;
        p = nex;
    }
    return {tail, head};
}

static ListNode* reverseKGroup(ListNode* head, int k) {
    if (head == nullptr ||head->next == nullptr) {
        return head;
    }

    ListNode dummy(0);
    dummy.next = head;
    ListNode* pre = &dummy;

    while (head) {
        ListNode* tail = pre;
        for (int i = 0; i < k; ++i) {
            tail = tail->next;
            if (!tail) {
                return dummy.next;
            }
        }
        ListNode* next = tail->next;
        tie(head, tail) = reverseList(head, tail);
        pre->next = head;
        tail->next = next;
        pre = tail;
        head = tail->next;
    }

    return dummy.next;
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
    if (n < k) {
        return head;
    }

    ListNode* ans = nodes[k-1];
    ListNode dummy(0);
    ListNode* pre = &dummy;

    int kgroups = n / k;

    stack<ListNode*> cur_k_node;
    if (n == k) {
        return ReverseList(head);
    }

    for (int i = 0; i < n; ++i) {
        cur_k_node.push(nodes[i]); 

        if ( i == kgroups * k - 1) {
            while (!cur_k_node.empty()) {
                ListNode* cur = cur_k_node.top();
                cur_k_node.pop();
                pre->next = cur;
                pre = cur;
            }

            pre->next = nodes[i+1];

            break;
        }

        if (((i+1) % k) == 0) {
            while (!cur_k_node.empty()) {
                ListNode* cur = cur_k_node.top();
                cur_k_node.pop();
                pre->next = cur;
                pre = cur;
            }
        }
    }

    return ans;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;

    int max = 100;
    int min = -100;
    int max_n = 20;
    int test_times = 50000;
    
    for (int i = 0; i < test_times; ++i) {

    }

    cout << "test end" << endl;
    return 0;
}