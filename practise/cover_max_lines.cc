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
    priority_queue<int, vector<int>, std::greater<int>> heap;
    int ans = 0;
    for (int i = 0; i < lines.size(); ++i) {
        while (!heap.empty() && heap.top() <= lines[i].first) {
            heap.pop();
        }

        heap.push(lines[i].second);
        ans = std::max(ans, (int)heap.size());
    }

    return ans;
}

static int maxCoverTest(vector<pair<int, int>> lines) {
    if (lines.empty()) {
        return 0;
    }

    int min_val = std::numeric_limits<int>::max();
    int max_val = std::numeric_limits<int>::min();
    for (auto& elem: lines) {
        min_val = std::min(elem.first, min_val);
        max_val = std::max(elem.second, max_val);
    }
    int ans = 0;
    for (int i = min_val; i < max_val; ++i) {
        double p = i + 0.5;
        int cur = 0;
        for (auto& elem: lines) {
            if (elem.first < p && elem.second > p) {
                cur++;
            }
        }
        ans = std::max(ans, cur);
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