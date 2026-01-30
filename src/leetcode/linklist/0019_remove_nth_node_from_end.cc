#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <queue>

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

static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Math::random() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(Math::random() * (max_val - min_val + 1)) + min_val;
		out.emplace_back(val);
	}
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
    https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
    19. 删除链表的倒数第 N 个结点
       给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
*/

static ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (n < 1 || head == nullptr) {
        return head;
    }

    int cnt = 0;
    ListNode* cur = head;
    while (cnt < n) {
        cur = cur->next;
        ++cnt;
    }

    ListNode dummy(0);
    dummy.next = head;
    ListNode* pre = &dummy;
    ListNode* slow = head;
    while (cur != nullptr) {
        pre->next = slow;
        pre = pre->next;
        slow = slow->next;
        cur = cur->next;
    }

    pre->next = slow->next;
    delete slow;
    return dummy.next;
}
    
static ListNode* test(ListNode* head, int n) {
    if (n < 1 || !head) {
        return head;
    }

    vector<ListNode*> nodes;
    ListNode* cur = head;
    while (cur != nullptr) {
        nodes.emplace_back(cur);
        cur = cur->next;
    }

    if (n == nodes.size()) {
        ListNode* ans = head->next;
        delete head;
        return ans;
    }

    int len = nodes.size();

    if (n == 1) {
        if (nodes.size() > 1) {
            delete nodes[len - 1];
            nodes[len - 2]->next = nullptr;
            return nodes[0];
        }
        else {
            delete head;
            return nullptr;
        }
    }

    int pos = nodes.size() - n;
    nodes[pos - 1]->next = nodes[pos]->next;
    delete nodes[pos];
    return nodes[0];
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
        int len = GetListLen(head1);
        int n = RandomVal(0, len);
        ListNode* ans1 = removeNthFromEnd(head1, n);
        ListNode* ans2 = test(head2, n);
        if (!IsEqual(ans1, ans2)) {
            cout << "test failed" << endl;
            PrintList(ans1);
            PrintList(ans2);
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