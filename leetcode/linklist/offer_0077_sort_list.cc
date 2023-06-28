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

static ListNode* RandomSortedList(int max_n, int min_val, int max_val) {
    vector<int> out;
    RandomArr(out, max_n, min_val, max_val);
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
    https://leetcode.cn/problems/7WHec2/
    offer 077 链表排序
        给定链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
*/
ListNode* merge(ListNode* head1, ListNode* head2) {
    ListNode dummy(0);
    ListNode* temp = &dummy, *temp1 = head1, *temp2 = head2;
    while (temp1 != nullptr && temp2 != nullptr) {
        if (temp1->val <= temp2->val) {
            temp->next = temp1;
            temp1 = temp1->next;
        } else {
            temp->next = temp2;
            temp2 = temp2->next;
        }
        temp = temp->next;
    }

    if (temp1 != nullptr) {
        temp->next = temp1;
    } else if (temp2 != nullptr) {
        temp->next = temp2;
    }

    return dummy.next;
}

ListNode* sortList(ListNode* head, ListNode* tail) {
    if (head == nullptr) {
        return head;
    }

    if (head->next == tail) {
        head->next = nullptr;
        return head;
    }

    ListNode* slow = head, *fast = head;
    while (fast != tail) {
        slow = slow->next;
        fast = fast->next;
        if (fast != tail) {
            fast = fast->next;
        }
    }

    ListNode* mid = slow;
    return merge(sortList(head, mid), sortList(mid, tail));
}

ListNode* sortList(ListNode* head) {
    return sortList(head, nullptr);
}

struct Comp {
    bool operator() (std::pair<int, ListNode*> a, std::pair<int, ListNode*> b) {
        return a.first > b.first;
    }
};

static ListNode* test(ListNode* list) {
    if (list == nullptr || list->next == nullptr) {
        return list;
    }

    priority_queue<std::pair<int, ListNode*>, 
        vector<std::pair<int, ListNode*>>, Comp> queue;

    while (list != nullptr) {
        queue.push(std::make_pair(list->val, list));
        list = list->next;
    }

    ListNode* ans = queue.top().second;
    ListNode* pre = ans;
    queue.pop();

    while (!queue.empty()) {
        pre->next = queue.top().second;
        queue.pop();
        pre = pre->next;
    }

    pre->next = nullptr;

    return ans;
}

int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int max = 100;
    int min = -100;
    int max_n = 10;
    int test_times = 100000;

    for (int i = 0; i < test_times; ++i) {
        ListNode* head1 = RandomSortedList(max_n, min, max);
        ListNode* head2 = CopyList(head1);
        ListNode* ans1 = sortList(head1);
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