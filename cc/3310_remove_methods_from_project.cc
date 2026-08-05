/*
 *
 * You are maintaining a project that has n methods numbered from 0 to n - 1.
 *
 * You are given two integers n and k, and a 2D integer array invocations, where
 * invocations[i] = [ai, bi] indicates that method ai invokes method bi.
 *
 * There is a known bug in method k. Method k, along with any method invoked by
 * it, either directly or indirectly, are considered suspicious and we aim to
 * remove them.
 *
 * A group of methods can only be removed if no method outside the group invokes
 * any methods within it.
 *
 * Return an array containing all the remaining methods after removing all the
 * suspicious methods. You may return the answer in any order. If it is not
 * possible to remove all the suspicious methods, none should be removed.
 *
 * */
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

namespace {

class Solution {
   public:
    vector<int> RemainingMethods(int n, int k,
                                 vector<vector<int>>& invocations) {
        vector<int> ret;
        auto size = n;
        std::vector<int> visited(size, 0);

        unordered_map<int, std::set<int>> adjusted;
        unordered_map<int, std::set<int>> adjustedfather;

        for (auto& p : invocations) {
            adjusted[p[0]].emplace(p[1]);
            adjustedfather[p[1]].emplace(p[0]);
        }

        queue<int> q;
        std::set<int> visitedset;
        q.emplace(k);

        while (!q.empty()) {
            auto p = q.front();
            visited[p] = 1;
            visitedset.emplace(p);

            q.pop();

            for (auto& v : adjusted[p]) {
                if (visited[v] == 0) {
                    q.emplace(v);
                }
            }
        }

        for (auto& v : visitedset) {
            for (auto& f : adjustedfather[v]) {
                if (visitedset.find(f) == visitedset.end()) {
                    return fullset(n);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (visited[i] == 0) {
                ret.push_back(i);
            }
        }

        return ret;
    }

    vector<int> fullset(int n) {
        vector<int> ret;
        ret.reserve(n);
        for (int i = 0; i < n; i++) {
            ret.push_back(i);
        }
        return ret;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(remainingMethods, t0) {
    int n = 4;
    int k = 1;
    vector<vector<int>> invocations{{1, 2}, {0, 1}, {3, 2}};
    Solution sl;
    auto ret = sl.RemainingMethods(n, k, invocations);
    vector<int> output{0, 1, 2, 3};
    EXPECT_EQ(output, ret);
    // Method 2 and method 1 are suspicious, but they are directly invoked by
    // methods 3 and 0, which are not suspicious. We return all elements without
    // removing anything.
}
TEST(remainingMethods, t1) {
    int n = 5;
    int k = 0;
    vector<vector<int>> invocations{{1, 2}, {0, 2}, {0, 1}, {3, 4}};
    Solution sl;
    auto ret = sl.RemainingMethods(n, k, invocations);
    vector<int> output{3, 4};
    EXPECT_EQ(output, ret);
    // Methods 0, 1, and 2 are suspicious and they are not directly invoked by
    // any other method. We can remove them.
}

TEST(remainingMethods, t2) {
    int n = 3;
    int k = 2;
    vector<vector<int>> invocations{{1, 2}, {0, 1}, {2, 0}};
    Solution sl;
    auto ret = sl.RemainingMethods(n, k, invocations);
    vector<int> output{};
    EXPECT_EQ(output, ret);
    // All methods are suspicious. We can remove them.
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
