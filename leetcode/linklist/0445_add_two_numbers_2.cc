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
    https://leetcode.cn/problems/add-two-numbers-ii/
    445. 两数相加 II
    给你两个 非空 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。
    将这两数相加会返回一个新的链表。
    你可以假设除了数字 0 之外，这两个数字都不会以零开头。
*/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    return nullptr;
}
    
ListNode* test(ListNode* l1, ListNode* l2) {
    return nullptr;
}
    
int main(int argc, char* argv[]) {
    cout << "test start..." << endl;

    int max = 9;
    int min = 0;
    int max_n = 100;
    int test_times = 10000;
    
    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomList(max_n, min, max);
        ListNode* head2 = RandomList(max_n, min, max);
        int len = GetListLen(head1);
        int n = RandomVal(0, len);
        ListNode* ans1 = addTwoNumbers(head1, head2);
        ListNode* ans2 = test(head1, head2);
        if (!IsEqual(ans1, ans2)) {
            cout << "test failed" << endl;
            FreeList(ans1);
            FreeList(ans2);
            FreeList(head1);
            FreeList(head2);
            break;
        }

        FreeList(ans1);
        FreeList(ans2);
        FreeList(head1);
        FreeList(head2);
    }

    cout << "test end" << endl;
    return 0;
}