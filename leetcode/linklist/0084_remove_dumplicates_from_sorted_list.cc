#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <map>
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
    https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/
    84. 删除排序链表中的重复元素 II
        定一个已排序的链表的头 head ，删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。
*/
ListNode* deleteDuplicates(ListNode* head) {
    if (!head) {
        return head;
    }
    
    ListNode* dummy = new ListNode(0);
    dummy->next = head;

    ListNode* cur = dummy;
    while (cur->next && cur->next->next) {
        if (cur->next->val == cur->next->next->val) {
            int x = cur->next->val;
            while (cur->next && cur->next->val == x) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }
        }
        else {
            cur = cur->next;
        }
    }

    ListNode* ans = dummy->next;
    delete dummy;

    return ans;
}

ListNode* test(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    } 

    map<int, int> key_n_map;
    ListNode* cur = head;
    while (cur != nullptr) {
        auto iter = key_n_map.find(cur->val);
        if (iter != key_n_map.end()) {
            int cnt = iter->second;
            key_n_map.erase(iter);
            key_n_map.insert({cur->val, cnt + 1});
        } else {
            key_n_map.insert({cur->val, 1});
        }
        cur = cur->next;
    }

    cur = head;
    vector<ListNode*> nodes;

    while (cur != nullptr) {
        auto iter = key_n_map.find(cur->val);
        if (iter->second == 1) {
            nodes.emplace_back(cur);
            cur = cur->next;
        } else {
            ListNode* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }

    if (nodes.size() == 0) {
        return nullptr;
    }

    for (int i = 1; i < nodes.size(); ++i) {
        nodes[i-1]->next = nodes[i];
    }
    nodes[nodes.size() - 1]->next = nullptr;

    return nodes[0];
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;

    int max = 100;
    int min = -100;
    int max_n = 20;
    int test_times = 50000;
    
    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomSortedList(max_n, min, max);
        ListNode* head2 = CopyList(head1);

        ListNode* ans1 = deleteDuplicates(head1);
        ListNode* ans2 = test(head2);
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