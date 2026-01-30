#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
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

static int RandomVal(int min, int max) {
    return (int)(Math::random() * (max - min)) + min;
}

static std::pair<int, int> RandomLR(int min, int max) {
    int val1 = RandomVal(min, max);
    int val2 = RandomVal(min, max);
    
    if (val1 <= val2) {
        return {val1, val2};
    } else {
        return {val2, val1};
    }
}

static int GetListLen(ListNode* head) {
    int ans = 0;
    while (head != nullptr) {
        ++ans;
        head = head->next;
    }

    return ans;
}

} // namespace

/*
    https://leetcode.cn/problems/reverse-linked-list-ii/
    92 反转链表2
        给你单链表的头指针head和两个整数left和right ，
        其中left <= right 请你反转从位置left到位置right的链表节点，
        返回反转后的链表 

*/
static std::pair<ListNode*, ListNode*> reverseList(ListNode* head, ListNode* tail) {
    ListNode* prev = tail->next;
    ListNode* cur = head;
    while (prev != tail) {
        ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return {tail, head};
}

static ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (head == nullptr || head->next == nullptr || left == right) {
        return head;
    }

    ListNode* cur = head;
    ListNode dummy(0);
    ListNode* prev = &dummy;
    prev->next = head;
    
    int i = 1;
    while (i < left) {
        prev->next = cur;
        prev = prev->next;
        cur = cur->next;
        ++i;
    }

    ListNode* rev_head = prev->next;
    ListNode* pos1 = prev;
    while (i <= right) {
        prev->next = cur;
        prev = prev->next;
        cur = cur->next;
        ++i;
    }

    prev->next = nullptr;
    tie(rev_head, prev) = reverseList(rev_head, prev);
    pos1->next = rev_head;
    prev->next = cur;
    
    return dummy.next;
}

static ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    while (head != nullptr) {
        ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    return prev;
}

static ListNode* test(ListNode* head, int left, int right) {
    if (head == nullptr || head->next == nullptr || left == right) {
        return head;
    }

    vector<ListNode*> nodes;
    while (head != nullptr) {
        nodes.emplace_back(head);
        head = head->next;
    }

    nodes[right - 1]->next = nullptr;
    ListNode* rev_head = reverseList(nodes[left - 1]);
    nodes[left-1]->next = right < nodes.size() ? nodes[right] : nullptr;
    
    if (left == 1) {
        return rev_head;
    } else {
        nodes[left-2]->next = rev_head;
        return nodes[0];
    }
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

        std::pair<int, int> lr = RandomLR(1, GetListLen(head1));
        ListNode* ans1 = reverseBetween(head1, lr.first, lr.second);
        ListNode* ans2 = test(head2, lr.first, lr.second);

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