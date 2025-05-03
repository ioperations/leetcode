// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    You are given an array of variable pairs equations and an array of real
    numbers values, where equations[i] = [Ai, Bi] and values[i] represent the
    equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a
   single variable.

    You are also given some queries, where queries[j] = [Cj, Dj] represents the
   jth query where you must find the answer for Cj / Dj = ?.

    Return the answers to all queries. If a single answer cannot be determined,
    return -1.0.

    Note: The input is always valid. You may assume that evaluating the queries
   will not result in division by zero and that there is no contradiction.

*/

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

#include <gtest/gtest.h>
namespace {
class Solution {
  unordered_map<string, unordered_map<string, double>> m_unmp;
  unordered_set<string> m_visited;

 public:
  double Dfs(string src, string dest) {
    m_visited.insert(src);
    if (src == dest && m_unmp.find(src) != m_unmp.end())
      return 1;  // if we reached destionation and  destionation string
                 // actually present in the graph
    for (auto it : m_unmp[src]) {
      if (m_visited.find(it.first) != m_visited.end()) continue;
      double const d = Dfs(it.first, dest);
      if (d > 0)
        return d * it.second;  // when returned value is > 0 means we are
                               // coming here after visiting destination
    }
    return -1;  // when destionation cannot be reached with from this
                // recursive call return -1
    }
    vector<double> CalcEquation(vector<vector<string>>& eq,
                                vector<double>& values,
                                vector<vector<string>>& queries) {
        for (int i = 0; i < (int)values.size();
             i++)  // this loop is for creating graph
        {
          m_unmp[eq[i][0]].insert({eq[i][1], values[i]});
          m_unmp[eq[i][1]].insert({eq[i][0], 1 / values[i]});
        }
        vector<double> ans;
        for (auto it : queries) {
          m_visited.clear();  // we clear visited array for each dfs
          ans.push_back(Dfs(
              it[0], it[1]));  // pushing answer of each query returned by dfs
        }
        return ans;
    }
};

TEST(evaluate_division, t1) {
    vector<vector<string>> equations{{"a", "b"}, {"b", "c"}};
    vector<double> values{2.0, 3.0};
    vector<vector<string>> queries{
        {"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
    vector<double> const output{6.00000, 0.50000, -1.00000, 1.00000, -1.00000};
    Solution sl;
    /*
        Given: a / b = 2.0, b / c = 3.0
        queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
        return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
    */
    auto ret = sl.CalcEquation(equations, values, queries);
    EXPECT_EQ(ret, output);
}

TEST(evaluate_division, t2) {
    vector<vector<string>> equations{{"a", "b"}, {"b", "c"}, {"bc", "cd"}};
    vector<double> values{1.5, 2.5, 5.0};
    vector<vector<string>> queries{
        {"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}};
    vector<double> const output{3.75000, 0.40000, 5.00000, 0.20000};
    Solution sl;
    auto ret = sl.CalcEquation(equations, values, queries);
    EXPECT_EQ(ret, output);
}

TEST(evaluate_division, t3) {
    vector<vector<string>> equations{{"a", "b"}};
    vector<double> values{0.5};
    vector<vector<string>> queries{
        {"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}};
    vector<double> const output{0.50000, 2.00000, -1.00000, -1.00000};
    Solution sl;
    auto ret = sl.CalcEquation(equations, values, queries);
    EXPECT_EQ(ret, output);
}

}  // namespace
