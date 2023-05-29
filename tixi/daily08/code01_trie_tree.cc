#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
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

static std::string GenRandomString() {
    int len = (int)(Math::random() * (64+1));
    stringstream ss;
    for (int i = 0; i < len; ++i) {
        char ch = (char)(Math::random()*26)  + 'a';
        ss << ch;
    }
    return ss.str();
}
static vector<std::string> GenRandomStringArray(int max_n) {
    int len = (int)(Math::random() * (max_n + 1));
    vector<string> ans;
    for (int i = 0; i < len; ++i) {
        ans.emplace_back(GenRandomString());
    }

    return ans;
}


class TrieTree {
public:
    TrieTree() {
        root_ = new TrieNode();
    }

    ~TrieTree() {
        if (root_ != nullptr) {
            FreeNode(root_);
        }
    }

    void Insert(std::string word) {
        if (word.empty()) {
            return;
        }

        int n = word.size();
        TrieNode* node = root_;
        for (int i = 0; i < n; ++i) {
            int index = word[i] - 'a';
            if (node->next[index] == nullptr) {
                node->next[index] = new TrieNode();
            }
            node = node->next[index];
            node->pass++;
        }
        node->end++;
    }

    void Delete(std::string word) {
        if (word.empty()) {
            return ;
        }

        if (Search(word) == 0) {
            return;
        }

        int n = word.size();
        TrieNode* node = root_;
        for (int i = 0; i < n; ++i) {
            int index = word[i] - 'a';
            if (--node->next[index]->pass == 0) {
                FreeNode(node->next[index]);
                node->next[index] = nullptr;
                return;
            }
            node = node->next[index];
        }
        node->end--;
    }

    int Search(std::string word) {
        if (word.empty()) {
            return 0;
        }

        int n = word.size();
        TrieNode* node = root_;
        for (int i = 0; i < n; ++i) {
            int index = word[i] - 'a';
            if (node->next[index] == nullptr) {
                return 0;
            }
            node = node->next[index];
        }

        return node->end;
    }

    int PrefixNumber(std::string prefix) {
        if (prefix.empty()) {
            return 0;
        }

        int n = prefix.size();
        TrieNode* node = root_;
        for (int i = 0; i < n; ++i) {
            int index = prefix[i] - 'a';
            if (node->next[index] == nullptr) {
                return 0;
            }
            node = node->next[index];
        }

        return node->pass;
    }

private:
    struct TrieNode {
        TrieNode* next[26] = {nullptr};
        int pass = 0;
        int end = 0;
    };

    void FreeNode(TrieNode* node) {
        if (node == nullptr) {
            return;
        }
        stack<TrieNode*> nodes;
        nodes.push(node);
        while (!nodes.empty()) {
            TrieNode* cur = nodes.top();
            nodes.pop();
            for (int i = 0; i < 26; ++i) {
                if (cur->next[i] != nullptr) {
                    nodes.push(cur->next[i]);
                }
            }
            delete cur;
            cur = nullptr;
        }
    }
private:
    TrieNode* root_ = nullptr;
};

class Test {
public:
    void Insert(std::string word) {
        if (word.empty()) {
            return;
        }

        auto iter = words.find(word);
        if (iter != words.end()) {
            int cnt = iter->second;
            words.erase(iter);
            words[word] = cnt + 1;
        } else {
            words[word] = 1;
        }
    }

    int Search(std::string word) {
        if (word.empty()) {
            return 0;
        }

        auto iter = words.find(word);
        if (iter != words.end()) {
            return iter->second;
        }

        return 0;
    }

    int PrefixNumber(std::string prefix) {
        if (prefix.empty()) {
            return  0;
        }
    
        int ans = 0;
        for (auto& elem: words) {
            if (elem.first.substr(0, prefix.size()) == prefix) {
                ans += elem.second;
            }
        }

        return ans;
    }

    void Delete(std::string word) {
        if (word.empty()) {
            return;
        }

        if (Search(word) == 0) {
            return;
        }

        auto cnt = words[word];
        words.erase(word);
        if (cnt != 1) {
           words[word] = cnt - 1;
        }
    }

private:
    std::map<std::string, int> words;
};

} // namespace


int main(int argc, char* argv[]) {
    cout << "test start..." << endl;
    int test_times = 10000;
    int max_n = 40;
    bool success = true;
    for (int i = 0; i < test_times; i++) {
        TrieTree trie_tree;
        Test test_tree;
        auto strs = GenRandomStringArray(max_n);
        for (int j = 0; j < strs.size(); j++) {
            double decide = Math::random();
            if (decide < 0.25) {
                trie_tree.Insert(strs[j]);
                test_tree.Insert(strs[j]);
            } else if (decide < 0.5) {
                trie_tree.Delete(strs[j]);
                test_tree.Delete(strs[j]);
            } else if (decide < 0.75) {
                int ans1 = trie_tree.Search(strs[j]);
                int ans2 = test_tree.Search(strs[j]);
                if (ans1 != ans2) {
                    success = false;
                    break;
                }
            } else {
                int ans1 = trie_tree.PrefixNumber(strs[j]);
                int ans2 = test_tree.PrefixNumber(strs[j]);
                if (ans1 != ans2) {
                    success = false;
                    break;
                }
            }
        }
        if (!success) {
            break;
        }
    }

    cout << (success ? "success" : "failed") << endl;

    cout << "test end" << endl;
    return 0;
}