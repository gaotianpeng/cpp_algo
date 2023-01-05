#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include "gtest/gtest.h"
#include "random.h"

using namespace std;
using namespace tools;

static bool sortCompactor(pair<int, int>& elem1, pair<int, int>& elem2) {
    return elem1.first < elem2.first;
}

static int maxCover(vector<pair<int, int>> lines) {
    if (lines.empty()) {
        return 0;
    }

    std::sort(lines.begin(), lines.end(), sortCompactor);
    priority_queue<int, vector<int>, greater<int>> heap;
    int ans = 0;
    for (int i = 0; i < lines.size(); ++i) {
        while (!heap.empty() && heap.top() <= lines[i].first) {
            heap.pop();
        }
        heap.push(lines[i].second);
        int heap_size = heap.size();
        ans = std::max(ans, heap_size);
    }

    return ans;
}

static int maxCoverTest(vector<pair<int, int>> lines) {
    if (lines.empty()) {
        return 0;
    }

    int min_val = numeric_limits<int>::max();
    int max_val = numeric_limits<int>::min();
    int n = lines.size();
    for (int i = 0; i < n; ++i) {
        min_val = std::min(min_val, lines[i].first);
        max_val = std::max(max_val, lines[i].second);
    }

    int ans = 0;
    for (int left = min_val; left < max_val; ++left) {
        int cur = 0;
        double p = left + 0.5;
        for (int i = 0; i < n; ++i) {
            if (lines[i].first < p && lines[i].second > p) {
                cur++;
            }
        }

        ans = std::max(cur, ans);
    }

    return ans;
}

static void generateRandomLines(int n, int left, int right, vector<pair<int, int>>& lines) {
    int size = Random::random(0, n);
    for (int i = 0; i < size; ++i) {
        int a = left + Random::random(0, right - left);
        int b = left + Random::random(0, right - left);
        if (a == b) {
            b = a + 1;
        }

        pair<int, int> line;
        line.first = std::min(a, b);
        line.second = std::max(a, b);
        lines.push_back(line);
    }
}

//TEST(PractiseTest, CoverMaxLinesTest) {
//    cout << "cover max lines test start\n";
//    int test_times = 50000;
//    int left = 10;
//    int right = 400;
//    int max_n = 100;
//    for (int i = 0; i < test_times; ++i) {
//        vector<pair<int, int>> lines;
//        generateRandomLines(max_n, left, right, lines);
//        if (maxCover(lines) != maxCoverTest(lines)) {
//            EXPECT_TRUE(false);
//        }
//    }
//
//    cout << "test success\n";
//    cout << "cover max lines test end\n\n";
//}