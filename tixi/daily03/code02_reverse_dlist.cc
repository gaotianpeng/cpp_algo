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

struct DListNode{
    int val  = 0;
    DListNode* next = nullptr;
    DListNode* last = nullptr;

    DListNode(int v):val(v) {
    }
};

static DListNode* RandomList(int max_n, int min_val, int max_val) {
    vector<int> out;
    RandomArr(out, max_n, min_val, max_val);
    vector<DListNode*> lists;
    for (auto& elem: out) {
        lists.emplace_back(new DListNode(elem));
    }

    for (int i = 1; i < lists.size(); ++i) {
        lists[i-1]->next = lists[i];
    }
    lists[lists.size() - 1]->next = nullptr;

    for (int i = lists.size() - 1; i > 0; --i) {
        lists[i-1]->last = lists[i];
    }
    lists[lists.size() - 1]->next = nullptr;
    lists[0]->last = nullptr;

    return lists[0];
}

static DListNode* CopyList(DListNode* head) {
    DListNode* ans = new DListNode(head->val);
    DListNode* ans_head = ans;
    ans_head->last = nullptr;

    while (head->next != nullptr) {
        ans->next = new DListNode(head->next->val);
        ans = ans->next;
        head = head->next;
    }

    DListNode* prev = nullptr;
    ans = ans_head;
    while (ans != nullptr) {
        ans->last = prev;
        prev = ans;
        ans = ans->next;
    }

    return ans_head;
}

static void PrintList(DListNode* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

static bool IsEqual(DListNode* head1, DListNode* head2) {
    assert(head1 != head2);
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


DListNode* ReverseDList(DListNode* head) {
    DListNode* pre = nullptr;
    DListNode* next = nullptr;
    while (head != nullptr) {
        next = head->next;
        head->next = pre;
        head->last = next;
        pre = head;
        head = next;
    }
    return pre;
}

DListNode* test(DListNode* head) {
    vector<DListNode*> lists;
    while (head != nullptr) {
        lists.emplace_back(head);
        head = head->next;
    }

    for (int i = lists.size() - 1; i > 0; --i) {
        lists[i]->next = lists[i-1];
    }
    lists[0]->next = nullptr;

    for (int i = 1; i < lists.size(); ++i) {
        lists[i-1]->last = lists[i];
    }
    lists[lists.size() - 1]->last = nullptr;

    return lists[lists.size()  - 1];
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 10;

    for (int i = 0; i < test_times; ++i) {
       DListNode* head1 = RandomList(max_n, min, max);
       DListNode* head2 = CopyList(head1);
       DListNode* rev1 = ReverseDList(head1);
       DListNode* rev2 = test(head2);

       if (!IsEqual(rev1, rev2)) {
            cout << "test failed" << endl;
            break;
       }
    }

    cout << "test end" << endl;

    return 0;
}