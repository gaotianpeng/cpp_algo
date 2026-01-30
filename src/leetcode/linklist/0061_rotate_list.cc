#include <algorithm>
#include <iostream>
#include <random>
#include <deque>
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

static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Math::random() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(Math::random() * (max_val - min_val + 1)) + min_val;
		out.emplace_back(val);
	}
}

static int RandomVal(int min, int max) {
    return (int)(Math::random()*(max - min + 1)) + min;
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
    https://leetcode.cn/problems/rotate-list/
    61 旋转链表
        给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。
*/
static ListNode* rotateRight(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr || k == 0) {
        return head;
    }

    ListNode* cur = head;
    int n = 0;

    ListNode dummy(0);
    ListNode* prev = &dummy;

    while (cur != nullptr) {
        ++n;
        prev->next = cur;
        prev = prev->next;
        cur = cur->next;
    }

    k = k % n;
    
    prev->next = head;

    int i = 0;
    cur = head;
    while (i < n - k) {
        prev->next = cur;
        prev = prev->next;
        cur = cur->next;
        ++i;
    }
    prev->next = nullptr;

    return cur;
}

static ListNode* test(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr || k == 0) {
        return head;
    }

    deque<ListNode*> nodes;
    ListNode* cur = head;
    while (cur != nullptr) {
        nodes.emplace_back(cur);
        cur = cur->next;
    }

    int n = nodes.size();
    k = k % n;
    int i = 0;
    while (i < k) {
        ListNode* cur = nodes.back();
        nodes.pop_back();
        nodes.emplace_front(cur);
        ++i;
    }

    nodes.back()->next = nullptr;

    ListNode dummy(0);
    ListNode* prev = &dummy;
    while (!nodes.empty()) {
        ListNode* cur = nodes.front();
        nodes.pop_front();
        prev->next = cur;
        prev = prev->next;
    }

    return dummy.next;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 10000;
    int min = -10000;
    int max_n = 30;
    int test_times = 50000;

    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomList(max_n, min, max);
        ListNode* head2 = CopyList(head1);
        int k = RandomVal(0, max_n);
        ListNode* ans1 = rotateRight(head1, k);
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
