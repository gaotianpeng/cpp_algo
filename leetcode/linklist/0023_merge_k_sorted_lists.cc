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

static void RandomSortedArr(vector<int>& out, int max_n, int min_val, int max_val) {
	int len = (int)(Math::random() * max_n);
	for (int i = 0; i < len; i++) {
		int val = (int)(Math::random() * (max_val - min_val + 1)) + min_val;
		out.emplace_back(val);
	}
    std::sort(out.begin(), out.end());
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

static ListNode* RandomSortedList(int max_n, int min_val, int max_val) {
    vector<int> out;
    RandomSortedArr(out, max_n, min_val, max_val);
    std::sort(out.begin(), out.end());
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

static ListNode* mergeTwoSortedList(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr) {
        return list2;
    }
    if (list2 == nullptr) {
        return list1;
    }

    ListNode dummy(0);
    ListNode* prev = &dummy;
    while (list1 != nullptr && list2 != nullptr) {
        auto& cur_node = list1->val <= list2->val ? list1 : list2;
        prev->next = cur_node;
        prev = prev->next;
        cur_node = cur_node->next;
    }

    while (list1 != nullptr) {
        prev->next = list1;
        prev = prev->next;
        list1 = list1->next;
    }

    while (list2 != nullptr) {
        prev->next = list2;
        prev = prev->next;
        list2 = list2->next;
    }

    return dummy.next;
}

static ListNode* merge(std::vector<ListNode*>& lists, int left, int right) {
    if (left == right) {
        return lists[left];
    }

    if (left > right) {
        return nullptr;
    }

    int mid = left + ((right - left) >> 1);

    return mergeTwoSortedList(merge(lists, left, mid), merge(lists, mid + 1, right));
}

static ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    return merge(lists, 0, lists.size() - 1);
}

ListNode* mergeKLists1(std::vector<ListNode*>& lists) {
    if (lists.empty()) {
        return nullptr;
    }

    int interval = 1;
    int n = lists.size();

    while (interval < n) {
        for (int i = 0; i < n - interval; i += interval * 2) {
            lists[i] = mergeTwoSortedList(lists[i], lists[i + interval]);
        }
        interval <<= 1;
    }

    return lists[0];
}
struct Comp {
    bool operator() (std::pair<ListNode*, int> a, std::pair<ListNode*, int> b) {
        return a.first->val > b.first->val;
    }
};

ListNode* test(vector<ListNode*>& lists) {
    if (lists.size() == 0) {
        return nullptr;
    }

    if (lists.size() == 1) {
        return lists[0];
    }

    int k = lists.size();
    int cur_pos = -1;
    priority_queue<std::pair<ListNode*, int>, std::vector<std::pair<ListNode*, int>>, Comp> min_heap;

    for (int i = 0; i < lists.size(); ++i) {
        ListNode* cur = lists[i];
        if (cur != nullptr) {
            min_heap.push({cur, i});
        }
    }

    if (min_heap.empty()) {
        return nullptr;
    }

    std::pair<ListNode*, int> head = min_heap.top();
    min_heap.pop();
    
    ListNode* ans = head.first;
    if (head.first->next != nullptr) {
        min_heap.push({head.first->next, head.second});
    }

    ListNode* pre = ans;
    while (!min_heap.empty()) {
        std::pair<ListNode*, int> cur_min = min_heap.top();
        min_heap.pop();
        pre->next = cur_min.first;
        if (cur_min.first->next != nullptr) {
            min_heap.push({cur_min.first->next, cur_min.second});
        }
        pre = pre->next;
    }
    pre ->next = nullptr;

    return ans;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;

    int max = 100;
    int min = -100;
    int max_n = 20;
    int test_times = 10000;
    int max_vec_n = 30;
    
    for (int i = 0; i < test_times; ++i) {
        int vec_n = RandomVal(0, max_vec_n);
        vector<ListNode*> list1;
        vector<ListNode*> list2;
        vector<ListNode*> list3;
        for (int j = 0; j < vec_n; ++j) {
            ListNode* head1 = RandomSortedList(max_n, min, max);
            ListNode* head2 = CopyList(head1);
            ListNode* head3 = CopyList(head1);
            list1.emplace_back(head1);
            list2.emplace_back(head2);
            list3.emplace_back(head3);
        }

        ListNode* ans1 = mergeKLists(list1);
        ListNode* ans2 = test(list2);
        ListNode* ans3 = mergeKLists1(list3);
        if (!IsEqual(ans1, ans2) || !IsEqual(ans2, ans3)) {
            cout << "test failed" << endl;
            FreeList(ans1);
            FreeList(ans2);
            FreeList(ans3);
            break;
        }

        FreeList(ans1);
        FreeList(ans2);
        FreeList(ans3);
    }

    cout << "test end" << endl;
    return 0;
}