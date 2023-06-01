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

static int GetRandomVal(ListNode* head) {
    vector<ListNode*> nodes;
    while (head != nullptr) {
        nodes.emplace_back(head);
        head = head->next;
    }

    int pos = RandomVal(0, nodes.size() - 1);
    return nodes[pos]->val;
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

} // namespace


/*
    将单向链表按某值划分成左边小、中间相等、右边大的形式
*/
static ListNode* SmallEqualBigger(ListNode* head, int val) {
    if (head == nullptr) {
        return nullptr;
    }

    ListNode* small_head = nullptr;
    ListNode* small_tail = nullptr;
    ListNode* equal_head = nullptr;
    ListNode* equal_tail = nullptr;
    ListNode* bigger_head = nullptr;
    ListNode* bigger_tail = nullptr;

    ListNode* next = nullptr;
    while (head != nullptr) {
        next = head->next;
        head->next = nullptr;
        if (head->val < val) {
            if (small_head == nullptr) {
                small_head = head;
                small_tail = head;
                small_tail->next = nullptr;
            } else {
                small_tail->next = head;
                small_tail = small_tail->next;
                small_tail->next = nullptr;
            }
        } else if (head->val == val) {
            if (equal_head == nullptr) {
                equal_head = head;
                equal_tail = head;
                equal_tail->next = nullptr;
            } else {
                equal_tail->next = head;
                equal_tail = equal_tail->next;
                equal_tail->next = nullptr;
            }
        } else {
            if (bigger_head == nullptr) {
                bigger_head = head;
                bigger_tail = head;
                bigger_tail->next = nullptr;
            } else {
                bigger_tail->next = head;
                bigger_tail = bigger_tail->next;
                bigger_tail->next = nullptr;
            }
        }
        head = next;
    }

    if (small_tail != nullptr) {
        small_tail->next = equal_head;
        equal_tail = equal_head == nullptr ? small_tail : equal_tail;
    }
    if (equal_tail != nullptr) {
        equal_tail->next = bigger_head;
    }

    return small_head != nullptr ? small_head :
        (equal_head != nullptr ? equal_head : bigger_head);
}

static ListNode* test(ListNode* head, int val) {
    if (head == nullptr) {
        return nullptr;
    }

    vector<ListNode*> nodes;
    while (head != nullptr) {
        nodes.emplace_back(head);
        head = head->next;
    }
    vector<ListNode*> ans;
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i]->val < val) {
            ans.emplace_back(nodes[i]);
        }
    }
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i]->val == val) {
            ans.emplace_back(nodes[i]);
        }
    }
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i]->val > val) {
            ans.emplace_back(nodes[i]);
        }
    }

    for (int i = 1; i < ans.size(); ++i) {
        ans[i - 1]->next = ans[i];
    }
    ans[ans.size() - 1]->next = nullptr;

    return ans[0];
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 10;

    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomList(max_n, min, max);
        ListNode* head2 = CopyList(head1);
        if (head1 == nullptr) {
            continue;
        }

        int val = GetRandomVal(head1);
        ListNode* list1 = SmallEqualBigger(head1, val);
        ListNode* list2 = test(head2, val);
        if (!IsEqual(list1, list2)) {
            cout << "test failed" << endl;
            break;
        }

        FreeList(list1);
        FreeList(list2);
    }

    cout << "test end" << endl;
    return 0;
}