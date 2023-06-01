#include <algorithm>
#include <iostream>
#include <random>
#include <set>
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

    double probability = Math::random();
    if (probability < 0.6) {
        lists[lists.size() - 1]->next = nullptr;
    } else {
        int pos = RandomVal(0, lists.size() - 1);
        lists[lists.size() - 1]->next = lists[pos];
    }
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
    set<ListNode*> nodes;
    bool has_loop = false;
    while (head != nullptr) {
        if (nodes.contains(head)) {
            has_loop = true;
            break;
        }
        nodes.insert(head);
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
    if (has_loop) {
        cout << "current linked list has loop" << endl;
    }
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

static std::pair<ListNode*, ListNode*> GenRandomList(
        int max_n, int min_val, int max_val) {
    ListNode* list1 = RandomList(max_n, min_val, max_val);
    ListNode* list2 = RandomList(max_n, min_val, max_val);

    double probability = Math::random();
    if (probability < 0.5) {
        return {list1, list2};
    }

    ListNode* cur = list1;
    vector<ListNode*> nodes1;
    set<ListNode*> sets1;
    while (cur != nullptr) {
        if (sets1.contains(cur)) {
            break;
        }
        sets1.insert(cur);
        nodes1.emplace_back(cur);
        cur = cur->next;
    }

    vector<ListNode*> nodes2;
    set<ListNode*> sets2;
    cur = list2;
    while (cur != nullptr) {
        if (sets2.contains(cur)) {
            break;
        }
        sets2.insert(cur);
        nodes2.emplace_back(cur);
        cur = cur->next;
    }
    
    ListNode* end2 = cur;

    if (nodes1.size() == 0 || nodes2.size() == 0) {
        return {list1, list2};
    } 

    int pos1 = RandomVal(0, nodes1.size() - 1);
    int pos2 = RandomVal(0, nodes2.size() - 1);
    cur = nodes2[pos2]->next;
    nodes2[pos2]->next = nodes1[pos1];

    vector<ListNode*> nodes3;
    while (cur != nullptr) {
        if (cur == end2) {
            break;
        }
        nodes3.emplace_back(cur);
        cur = cur->next;
    }

    for (auto& elem: nodes3) {
        delete elem;
    }

    return {list1, list2};
}

static void FreeList(std::pair<ListNode*, ListNode*> lists) {
    std::set<ListNode*> nodes;
    ListNode* head = lists.first;
    while (head != nullptr) {
        if (nodes.contains(head)) {
            break;
        }
        nodes.insert(head);
        head = head->next;
    }
    head = lists.second;
    while (head != nullptr) {
        if (nodes.contains(head)) {
            break;
        }
        nodes.insert(head);
        head = head->next;
    }

    for (auto& elem: nodes) {
        delete elem;
    }
}

} // namespace


/*
    给定两个可能有环也可能无环的单链表，头节点head1 和 head2。请实现一个函数，如果两个链表相交，
    请返回相交的 第一个节点。如果不相交，返回null
    【要求】
        如果两个链表长度之和为N，时间复杂度请达到O(N)，额外空间复杂度 请达到O(1)
*/
static ListNode* FindFirstIntersection(ListNode* head1, ListNode* head2) {
    return nullptr;
}

static ListNode* test(ListNode* head1, ListNode* head2) {
    return nullptr;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 100;

    for (int i = 0; i < test_times; ++i) {
        std::pair<ListNode*, ListNode*> lists = GenRandomList(max_n, min, max);
        PrintList(lists.first);
        PrintList(lists.second);
        FreeList(lists);
    }

    cout << "test end" << endl;
    return 0;
}