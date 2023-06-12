#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <assert.h>
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

static ListNode* ReverseList(ListNode* head) {
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
/*
    https://leetcode.cn/problems/reorder-list/
    141 重排链表
        给定一个单链表 L 的头节点 head ，单链表 L 表示为
        L0 → L1 → … → Ln - 1 → Ln
        请将其重新排列后变为：
        L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → 
*/
void ReOrder(ListNode* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return ;
    }

    ListNode* slow = head->next;
    ListNode* fast = head->next->next;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode* reverse = slow->next;
    slow->next = nullptr;
    reverse = ReverseList(reverse);

    while (head != nullptr && reverse != nullptr) {
        ListNode* next1 = head->next;
        ListNode* next2 = reverse->next;
        head->next = reverse;
        reverse->next = next1;
        head = next1;
        reverse = next2;
    }
}

void test(ListNode* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return ;
    }

    vector<ListNode*> nodes;
    ListNode* cur = head;
    while (cur != nullptr) {
        nodes.emplace_back(cur);
        cur = cur->next;
    }

    int n = nodes.size();
    int i = 0;

    for (int i = 0; i < n/2; ++i) {
        nodes[i]->next = nodes[ n - i - 1];
        nodes[n - i - 1]->next = nodes[i+1];
    }
    
    nodes[n/2]->next = nullptr;
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
       ReOrder(head1);
       test(head2);

       if (!IsEqual(head1, head2)) {
            cout << "test failed" << endl;
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