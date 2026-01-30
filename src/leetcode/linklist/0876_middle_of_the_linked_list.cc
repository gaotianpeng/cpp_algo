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

} // namespace

/*
    https://leetcode.cn/problems/middle-of-the-linked-list/
    876 链表的中间结点
        给你单链表的头结点 head ，请你找出并返回链表的中间结点。
        如果有两个中间结点，则返回第二个中间结点。

*/
static ListNode* middleNode(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* pre = nullptr;
    while (fast && fast->next) {
        fast = fast->next->next;
        pre = slow;
        slow = slow->next;
    }

    return pre->next;
}

static ListNode* test(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    vector<ListNode*> nodes;
    while (head != nullptr) {
        nodes.emplace_back(head);
        head = head->next;
    }


    return nodes[nodes.size()/2];
}


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 10000;
    int min = -10000;
    int max_n = 20;
    int test_times = 50000;


    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomList(max_n, min, max);
        ListNode* head2 = CopyList(head1);

        ListNode* mid1 = middleNode(head1);
        ListNode* mid2 = test(head2);
        if (mid1 == nullptr &&  mid2 != nullptr) {
            cout << "test failed " << endl;
            FreeList(head1);
            FreeList(head2);
            break;
        } else if (mid1 != nullptr &&  mid2 == nullptr) {
            cout << "test failed " << endl;
            FreeList(head1);
            FreeList(head2);
            break;
        } else {
            if (mid1 != nullptr && mid2 != nullptr) {
                if (mid1->val != mid2->val) {
                    cout << "test failed " << endl;
                    FreeList(head1);
                    FreeList(head2);
                    break;
                }
            }
        }

        FreeList(head1);
        FreeList(head2);
    }

    cout << "test end" << endl;

    return 0;
}