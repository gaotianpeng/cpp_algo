#include <algorithm>
#include <iostream>
#include <random>
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

static void RandomArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Math::random() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(Math::random() * (max_val - min_val + 1)) + min_val;
		out.emplace_back(val);
	}
}

static int RandomVal(int min_val, int max_val) {
    return (int)(Math::random() * (max_val - min_val + 1)) + min_val;
}

struct ListNode{
    int val  = 0;
    ListNode* next = nullptr;

    ListNode(int v):val(v) {
    }
};

static ListNode* RandomNormalList(int max_n, int min_val, int max_val) {
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

static ListNode* RandomPalindromeist(int max_n, int min_val, int max_val) {
    vector<int> out;
    RandomArr(out, max_n/2, min_val, max_val);
    vector<ListNode*> lists;
    ListNode* tail = nullptr;
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
    tail = lists[lists.size() - 1];
    if (Math::random() < 0.5) {
        tail->next = new ListNode(RandomVal(min_val, max_val));
        tail = tail->next;
    }

    for (int i = lists.size() - 1; i >= 0; --i) {
        tail->next = new ListNode(lists[i]->val);
        tail = tail->next;
    }
    tail->next = nullptr;

    return lists[0];
}

static ListNode* RandomList(int max_n, int min_val, int max_val) {
    ListNode* ans = nullptr;
    if (Math::random() < 0.6) {
        ans = RandomPalindromeist(max_n, min_val, max_val);
    } else {
        ans = RandomNormalList(max_n, min_val, max_val);
    }

    return ans;
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

static void FreeList(ListNode* head) {
    while (head != nullptr) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

} // namespace

/*
    给定一个单链表的头节点head，请判断该链表是否为回文结构
*/
static bool IsPalindromeList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }
    ListNode* cur = head;
    stack<ListNode*> nodes;
    while (cur != nullptr) {
        nodes.push(cur);
        cur = cur->next;
    }
    while (!nodes.empty()) {
        ListNode* cur = nodes.top();
        nodes.pop();
        if (cur->val != head->val) {
            return false;
        }
        head = head->next;
    }
    return true;
}

static bool test(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }

    vector<ListNode*> nodes;
    while (head != nullptr) {
        nodes.emplace_back(head);
        head = head->next;
    }

    int n = nodes.size();
    for (int i = 0; i < n; ++i) {
        if (nodes[i]->val != nodes[n - i - 1]->val) {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
       ListNode* head1 = RandomList(max_n, min, max);
       ListNode* head2 = CopyList(head1);
       bool ret1 = IsPalindromeList(head1);
       bool ret2 = test(head2);
       if (ret1 != ret2) {
            cout << "test failed" << endl;
            break;
       }
       FreeList(head1);
       FreeList(head2);
    }

    cout << "test end" << endl;
    return 0;
}