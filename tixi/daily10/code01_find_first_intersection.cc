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
    int cnt = 0;
    vector<int> out;
    RandomArr(out, max_n, min_val, max_val);
    vector<ListNode*> lists;
    for (auto& elem: out) {
        lists.emplace_back(new ListNode(elem));
        ++cnt;
    }

    if (lists.size() == 0) {
        return nullptr;
    }

    for (int i = 0; i < lists.size() - 1; ++i) {
        lists[i]->next = lists[i + 1];
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

    if (nodes1.size() == 0 || nodes2.size() == 0) {
        return {list1, list2};
    } 

    int pos1 = RandomVal(0, nodes1.size() - 1);
    int pos2 = RandomVal(0, nodes2.size() - 1);
    nodes2[pos2]->next = nodes1[pos1];
    for (int i = pos2 + 1; i < nodes2.size(); ++i) {
        delete nodes2[i];
    }

    return {list1, list2};
}

static void FreeList(std::pair<ListNode*, ListNode*> lists) {
    std::set<ListNode*> nodes1;
    ListNode* head = lists.first;
    while (head != nullptr) {
        if (nodes1.contains(head)) {
            break;
        }
        nodes1.insert(head);
        head = head->next;
    }
    head = lists.second;

    std::set<ListNode*> nodes2;
    while (head != nullptr) {
        if (nodes2.contains(head)) {
            break;
        }
        nodes2.insert(head);
        head = head->next;
    }

    for (auto& elem: nodes2) {
        if (!nodes1.contains(elem)) {
            nodes1.insert(elem);
        }
    }

    for (auto& elem: nodes1) {
        delete elem;
    }
}

static void PrintList(std::pair<ListNode*, ListNode*> lists) {
    std::set<ListNode*> nodes1;
    std::vector<ListNode*> list1;
    ListNode* head = lists.first;
    while (head != nullptr) {
        if (nodes1.contains(head)) {
            break;
        }
        nodes1.insert(head);
        list1.emplace_back(head);
        head = head->next;
    }
    head = lists.second;

    std::set<ListNode*> nodes2;
    std::vector<ListNode*> list2;
    while (head != nullptr) {
        if (nodes2.contains(head)) {
            break;
        }
        nodes2.insert(head);
        list2.emplace_back(head);
        head = head->next;
    }

    for (int i = 0; i < list1.size(); ++i) {
        cout << list1[i] << " ";
    }
    cout << endl;


    for (int i = 0; i < list2.size(); ++i) {
        cout << list2[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < list1.size(); ++i) {
        cout << list1[i]->val << " ";
    }
    cout << endl;


    for (int i = 0; i < list2.size(); ++i) {
        cout << list2[i]->val << " ";
    }
    cout << endl;

}

} // namespace

static ListNode* GetLoopNodeTest(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }

    set<ListNode*> nodes;
    while (head != nullptr) {
        if (nodes.contains(head)) {
            return head;
        }
        nodes.insert(head);
        head = head->next;
    }

    return nullptr;
}

static ListNode* GetLoopNode(ListNode* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return nullptr;
    }


    ListNode* slow = head->next;
    ListNode* fast = head->next->next;
    while (slow != fast) {
        if (fast->next == nullptr || fast->next->next == nullptr) {
            return nullptr;
        }
        slow = slow->next;
        fast = fast->next->next;
    }

    fast = head;
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}

static ListNode* BothLoop(ListNode* loop1, ListNode* loop2, ListNode* head1, ListNode* head2) {
    ListNode* cur1 = nullptr;
    ListNode* cur2 = nullptr;
    if (loop1 == loop2) {
        cur1 = head1;
        cur2 = head2;
        int n = 0;
        while (cur1 != loop1) {
            ++n;
            cur1 = cur1->next;
        }

        while (cur2 != loop1) {
            --n;
            cur2 = cur2->next;
        }

        cur1 = n > 0 ? head1 : head2;
        cur2 = cur1 == head1 ? head2 : head1;

        n = std::abs(n);
        while ( n > 0) {
            --n;
            cur1 = cur1->next;
        }

        while (cur1 != cur2) {
            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        return cur1;
    } else {
        cur1 = loop1->next;
        while (cur1 != loop1) {
            if (cur1 == loop2) {
                return loop2;
            }
            cur1 = cur1->next;
        }

        return nullptr;
    }
}

static ListNode* NoLoop(ListNode* head1, ListNode* head2) {
    if (head1 == nullptr || head2 == nullptr) {
        return nullptr;
    }

    int n = 0;
    ListNode* cur1 = head1;
    ListNode* cur2 = head2;
    while (cur1 != nullptr) {
        ++n;
        cur1 = cur1->next;
    }

    while (cur2 != nullptr) {
        --n;
        cur2 = cur2->next;
    }

    if (cur1 != cur2) {
        return nullptr;
    }

    cur1 = n > 0 ? head1 : head2;
    cur2 = cur1 == head1 ? head2 : head1;

    n = std::abs(n);

    while (n > 0) {
        --n;
        cur1 = cur1->next;
    }

    while (cur1 != cur2) {
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    return cur1;
}

/*
    给定两个可能有环也可能无环的单链表，头节点head1 和 head2。请实现一个函数，如果两个链表相交，
    请返回相交的 第一个节点。如果不相交，返回null
    【要求】
        如果两个链表长度之和为N，时间复杂度请达到O(N)，额外空间复杂度 请达到O(1)
*/

static ListNode* getIntersectionNode(ListNode* head1, ListNode* head2) {
    if (head1 == nullptr || head2 == nullptr) {
        return nullptr;
    }

    ListNode* loop1 = GetLoopNode(head1);
    ListNode* loop2 = GetLoopNode(head2);

    if (loop1 != nullptr && loop2 != nullptr) {
        return BothLoop(loop1, loop2, head1, head2);
    }

    if (loop1 == nullptr && loop2 == nullptr) {
        return NoLoop(head1, head2);
    }

    return nullptr;
}

static ListNode* test(ListNode* head1, ListNode* head2) {
    if (head1 == nullptr || head2 == nullptr) {
        return nullptr;
    }
    
    set<ListNode*> set1;
    vector<ListNode*> nodes1;
    ListNode* head = head1;
    while (head != nullptr) {
        auto iter = set1.find(head);
        if (iter != set1.end()) {
            break;
        }
        nodes1.emplace_back(head);
        set1.insert(head);
        head = head->next;
    }

    set<ListNode*> set2;
    vector<ListNode*> nodes2;
    head = head2;
    while (head != nullptr) {
        auto iter = set2.find(head);
        if (iter != set2.end()) {
            break;
        }
        nodes2.emplace_back(head);
        set2.insert(head);
        head = head->next;
    }

    for (auto& elem: nodes2) {
        for (auto& target : nodes1) {
            if (target == elem) {
                return target;
            }
        }
    }

    return nullptr;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 30;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        std::pair<ListNode*, ListNode*> lists = GenRandomList(max_n, min, max);
        if (getIntersectionNode(lists.first, lists.second) != test(lists.first, lists.second)){
            PrintList(lists);
            FreeList(lists);
            break;
        }

        FreeList(lists);
    }

    cout << "test end" << endl;
    return 0;
}