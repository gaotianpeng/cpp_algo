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

/*
    https://leetcode.cn/problems/merge-two-sorted-lists/
    0021 合并两个有序链表
        将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的
*/
static ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr) {
        return list2;
    }

    if (list2 == nullptr) {
        return list1;
    }

    ListNode* ans = list1->val < list2->val ? list1: list2;
    if (ans == list1) {
        list1 = list1->next;
    } else {
        list2 = list2->next;
    }

    ListNode* pre = ans;

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val <= list2->val) {
            pre->next = list1;
            list1 = list1->next;
        } else {
            pre->next = list2;
            list2 = list2->next;
        }

        pre = pre->next;
    }

    pre->next = list1 != nullptr ? list1 : list2;

    return ans;
}

static ListNode* merge(vector <ListNode*> &lists, int l, int r) {
    if (l == r) return lists[l];
    if (l > r) return nullptr;
    int mid = (l + r) >> 1;
    return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
}

static ListNode* mergeKLists(vector<ListNode*>& lists) {
    return merge(lists, 0, lists.size() - 1);
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
        for (int j = 0; j < vec_n; ++j) {
            ListNode* head1 = RandomSortedList(max_n, min, max);
            ListNode* head2 = CopyList(head1);
            list1.emplace_back(head1);
            list2.emplace_back(head2);
        }

        ListNode* ans1 = mergeKLists(list1);
        ListNode* ans2 = test(list2);
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