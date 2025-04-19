/**
 * You are given an integer limit and a 2D array queries of size n x 2.
 * There are limit + 1 balls with distinct labels in the range [0, limit].
 * Initially, all balls are uncolored. For every query in queries that is of the
 * form [x, y], you mark ball x with the color y. After each query, you need to
 * find the number of distinct colors among the balls.
 *
 * Return an array result of length n, where result[i] denotes the number of
 * distinct colors after ith query.
 *
 * Note that when answering a query, lack of a color will not be considered as a
 * color.
 *
 */

#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
   public:
    vector<int> QueryResults(int limit, vector<vector<int>> &queries) {
        /*
          1 <= limit <= 109
          1 <= n == queries.length <= 105
          queries[i].length == 2
          0 <= queries[i][0] <= limit
          1 <= queries[i][1] <= 109
         */
        auto size = queries.size();
        vector<int> ret(size, 0);
        unordered_map<int, int> hm;
        unordered_map<int, int> table;

        for (size_t i = 0; i < size; i++) {
            auto &curr = queries[i];
            int index = curr[0];
            if (!(table.count(index) == 0 or table[index] == 0)) {
                int c = table[index];
                hm[c]--;
                if (hm[c] == 0) {
                    hm.erase(c);
                }
            }
            int color = curr[1];
            hm[color]++;
            table[index] = color;
            ret[i] = hm.size();
        }
        return ret;
    }

    vector<int> QueryResultsV0(int limit, vector<vector<int>> &queries) {
        // FIXME: memory limit exceeded
        /*
         1 <= limit <= 109
         1 <= n == queries.length <= 105
         queries[i].length == 2
         0 <= queries[i][0] <= limit
         1 <= queries[i][1] <= 109
         */
        auto size = queries.size();
        vector<int> ret(size, 0);
        unordered_map<int, int> hm;
        vector<int> table(limit + 1, 0);

        for (size_t i = 0; i < size; i++) {
            auto &curr = queries[i];
            int index = curr[0];
            if (!(table[index] == 0)) {
                int c = table[index];
                hm[c]--;
                if (hm[c] == 0) {
                    hm.erase(c);
                }
            }
            int color = curr[1];
            hm[color]++;
            table[index] = color;
            ret[i] = hm.size();
        }
        return ret;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    int const limit = 4;
    vector<vector<int>> queries = {{1, 4}, {2, 5}, {1, 3}, {3, 4}};

    vector<int> const output = {1, 2, 2, 3};
    Solution sl;
    auto ret = sl.QueryResults(limit, queries);
    EXPECT_EQ(ret, output);
    ret = sl.QueryResultsV0(limit, queries);
    EXPECT_EQ(ret, output);

    /*
      Explanation:
          After query 0, ball 1 has color 4.
          After query 1, ball 1 has color 4, and ball 2 has color 5.
          After query 2, ball 1 has color 3, and ball 2 has color 5.
          After query 3, ball 1 has color 3, ball 2 has color 5, and ball 3 has
          color 4.
      */
}

TEST(t0, t2) {
    int const limit = 5;
    vector<vector<int>> queries = {{0, 1}, {1, 2}, {2, 2}, {3, 4}, {4, 5}};

    vector<int> const output = {1, 2, 2, 3, 4};
    Solution sl;
    auto ret = sl.QueryResults(limit, queries);
    EXPECT_EQ(ret, output);
    ret = sl.QueryResultsV0(limit, queries);
    EXPECT_EQ(ret, output);

    /*
     * After query 0, ball 0 has color 1.
       After query 1, ball 0 has color 1, and ball 1 has color 2.
       After query 2, ball 0 has color 1, and balls 1 and 2 have color 2.
       After query 3, ball 0 has color 1, balls 1 and 2 have color 2, and ball 3
       has color 4. After query 4, ball 0 has color 1, balls 1 and 2 have color
      2, ball 3 has color 4, and ball 4 has color 5.
       */
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
