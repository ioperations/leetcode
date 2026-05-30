/*
 *
There exists an infinite number line, with its origin at 0 and extending
towards the positive x-axis.
You are given a 2D array queries, which contains two types of queries:
For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x
from the origin. It is guaranteed that there is no obstacle at distance x when
the query is asked. For a query of type 2, queries[i] = [2, x, sz]. Check if it
is possible to place a block of size sz anywhere in the range [0, x] on the
line, such that the block entirely lies in the range [0, x]. A block cannot be
placed if it intersects with any obstacle, but it may touch it. Note that you do
not actually place the block. Queries are separate. Return a boolean array
results, where results[i] is true if you can place the block specified in the
ith query of type 2, and false otherwise.

1 <= queries.length <= 15 * 104
2 <= queries[i].length <= 3
1 <= queries[i][0] <= 2
1 <= x, sz <= min(5 * 104, 3 * queries.length)
The input is generated such that for queries of type 1, no obstacle exists at
distance x when the query is asked. The input is generated such that there is at
least one query of type 2.

 * */

#include <iostream>
#include <vector>
using namespace std;

namespace {

class Solution {
   public:
    Solution() = default;
    Solution(const Solution&) = delete;
    Solution(Solution&&) = default;
    ~Solution() = default;
    Solution& operator=(const Solution&) = default;
    Solution& operator=(Solution&&) = default;
    vector<bool> GetResults(vector<vector<int>>& queries) {
        vector<bool> ret;
        for (auto& ppp : queries) {
            if (ppp.empty()) {
                continue;
            }

            auto type = ppp[0];
            if (type == 1) {
                Buildobstacle(ppp[1]);
            } else if (type == 2) {
                auto res = DoQuery(ppp[1], ppp[2]);
                ret.emplace_back(res);
            }
        }

        for (auto kss : m_distance_after_x) {
            std::cout << kss << std::endl;
        }
        return ret;
    }

    void Buildobstacle(int x) {
        auto currentsize = static_cast<int>(m_distance_after_x.size());
        if (x < currentsize) {
            for (int i = x - 1; i >= 0; i--) {
                if (m_distance_after_x[i] == 1) {
                    break;
                }
                m_distance_after_x[i] = x - i;
            }
        } else {
            m_distance_after_x.resize(x, 0);
            for (int i = currentsize; i < x; i++) {
                m_distance_after_x[i] = x - i;
            }
        }
    }
    bool DoQuery(int x, int sz) {
        // For each query of type 2, we just need to check if max(d[0], d[1],
        // d[2], …d[x - sz]) > sz.
        auto currentsize = static_cast<int>(m_distance_after_x.size());
        if (x > currentsize) {
            if (x - currentsize >= sz) {
                return true;
            }
        }

        for (int i = 0; i < currentsize; i++) {
            if (m_distance_after_x[i] >= sz) {
                return true;
            }
        }
        return false;
    }

   private:
    std::vector<int> m_distance_after_x;
};
}  // namespace

#include <gtest/gtest.h>

TEST(getResult, t0) {
    std::vector<vector<int>> queries = std::vector<std::vector<int>>{
        std::vector<int>{1, 2}, std::vector<int>{2, 3, 3},
        std::vector<int>{2, 3, 1}, std::vector<int>{2, 2, 2}};
    std::vector<bool> output = std::vector<bool>{false, true, true};
    Solution sl;
    auto ret = sl.GetResults(queries);
    EXPECT_EQ(output, ret);
}

TEST(getResult, t1) {
    std::vector<vector<int>> queries = std::vector<std::vector<int>>{
        std::vector<int>{1, 7}, std::vector<int>{2, 7, 6},
        std::vector<int>{1, 2}, std::vector<int>{2, 7, 5},
        std::vector<int>{2, 7, 6}};
    std::vector<bool> output = std::vector<bool>{true, true, false};
    Solution sl;
    auto ret = sl.GetResults(queries);
    EXPECT_EQ(output, ret);
}

TEST(getResult, t2) {
    std::vector<vector<int>> queries = std::vector<std::vector<int>>{
        std::vector<int>{1, 1}, std::vector<int>{1, 11}, std::vector<int>{1, 4},
        std::vector<int>{1, 8}, std::vector<int>{2, 13, 7}};
    std::vector<bool> output = std::vector<bool>{false};
    Solution sl;
    auto ret = sl.GetResults(queries);
    EXPECT_EQ(output, ret);
}

TEST(getResult, t3) {
    std::vector<vector<int>> queries = std::vector<std::vector<int>>{
        std::vector<int>{1, 1}, std::vector<int>{2, 4, 3}};
    std::vector<bool> output = std::vector<bool>{true};
    Solution sl;
    auto ret = sl.GetResults(queries);
    EXPECT_EQ(output, ret);
}

TEST(getResult, t4) {
    std::vector<vector<int>> queries = std::vector<std::vector<int>>{
        std::vector<int>{1, 4}, std::vector<int>{2, 1, 2}};
    std::vector<bool> output = std::vector<bool>{true}; // wrong answer

    Solution sl;
    auto ret = sl.GetResults(queries);
    EXPECT_EQ(output, ret);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
