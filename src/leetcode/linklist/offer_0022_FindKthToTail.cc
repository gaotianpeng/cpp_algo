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
    return (int)(Math::random() * (max_val - min_val)) + min_val;
}

struct ListNode {
    int val = 0;
    ListNode* next = nullptr;

    ListNode(int v) :val(v) {
    }
};

static ListNode* RandomList(int max_n, int min_val, int max_val) {
    vector<int> out;
    RandomArr(out, max_n, min_val, max_val);
    vector<ListNode*> lists;
    for (auto& elem : out) {
        lists.emplace_back(new ListNode(elem));
    }

    if (lists.size() == 0) {
        return nullptr;
    }

    for (int i = 1; i < lists.size(); ++i) {
        lists[i - 1]->next = lists[i];
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
    https://leetcode.cn/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/
    剑指Offer 22 链表中倒数第k个节点
        输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。
        例如，一个链表有 6 个节点，从头节点开始，它们的值依次是 1、2、3、4、5、6。这个链表的倒数第 3 个节点是值为 4 的节点

        给定一个链表: 1->2->3->4->5, 和 k = 2.
        返回链表 4->5.
*/
static ListNode* getKthFromEnd(ListNode* head, int k) {
    if (head == nullptr || k < 1) {
        return nullptr;
    }

    ListNode* cur = head;
    int n = 0;
    while (cur != nullptr) {
        ++n;
        cur = cur->next;
    }

    if (n < k) {
        return nullptr;
    }

    if (n == k) {
        return head;
    }

    int step = n - k;
    cur = head;
    while (step > 0) {
        cur = cur->next;
        --step;
    }

    return cur;
}

static ListNode* test(ListNode* head, int k) {
    if (head == nullptr || k < 1) {
        return nullptr;
    }

    vector<ListNode*> nodes;
    while (head != nullptr) {
        nodes.emplace_back(head);
        head = head->next;
    }

    if (k > nodes.size()) {
        return nullptr;
    }

    return nodes[nodes.size() - k];
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 10;
    int test_times = 100000;
    int max_k = 20;

    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomList(max_n, min, max);
        ListNode* head2 = CopyList(head1);
        int k = RandomVal(0, max_k);
        ListNode* ans1 = getKthFromEnd(head1, k);
        ListNode* ans2 = test(head2, k);

        if (!IsEqual(ans1, ans2)) {
            cout << "test failed" << endl;
            PrintList(ans1);
            PrintList(ans2);

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