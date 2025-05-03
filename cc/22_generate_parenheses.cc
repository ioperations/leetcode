// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given n pairs of parentheses, write a function to generate all combinations of
well-formed parentheses.
*/

#include <set>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<string> GenerateParenthesisV2(int n) {
        if (n == 1) {
            return vector<string>{"()"};
        } else {
            auto ret_sub = GenerateParenthesis(n - 1);
            std::set<string> t;
            for (auto& ptr : ret_sub) {
                AddAnotherPair(ptr, t);
            }

            vector<string> ret(t.begin(), t.end());
            return ret;
        }

        return vector<string>{""};
    }

    /**
     * @brief  根据s 插入一个有效的括号对 把所有结果插入 @t 中
     * @param
     * @return
     */
    void AddAnotherPair(const std::string& s, std::set<std::string>& t) {
        // pass
    }

    void Parentheses(vector<string>& pvec, string s, int l, int r) {
        // pvec: result
        // s: current string
        // l: left parentheses number
        // r: right parentheses number

        string temp1 = s;
        string temp2 = s;
        if (l > 0) {
            temp1 += "(";
            Parentheses(pvec, temp1, l - 1, r + 1);
        }
        if (r > 0) {
            temp2 += ")";
            Parentheses(pvec, temp2, l, r - 1);
        } else if (l == 0 && r == 0) {
            pvec.push_back(s);
        }
    }

    vector<string> GenerateParenthesis(int n) {
        vector<string> res;
        Parentheses(res, "", n, 0);

        return res;
    }
};

TEST(generate_parenheses, t1) {
  int const n = 3;
  std::vector<string> expected = {"((()))", "(()())", "(())()", "()(())",
                                  "()()()"};
  std::set<string> const expected_set(expected.begin(), expected.end());
  Solution sl;
  auto ret = sl.GenerateParenthesis(n);

  std::set<string> const ret_set(ret.begin(), ret.end());

  EXPECT_EQ(ret_set, expected_set);
}

TEST(generate_parenheses, t2) {
  int const n = 1;
  std::vector<string> expected = {
      "()",
  };
  std::set<string> const expected_set(expected.begin(), expected.end());
  Solution sl;
  auto ret = sl.GenerateParenthesis(n);

  std::set<string> const ret_set(ret.begin(), ret.end());

  EXPECT_EQ(ret_set, expected_set);
}

}  // namespace
