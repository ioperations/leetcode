// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a string expression of numbers and operators, return all possible
results from computing all the different possible ways to group numbers and
operators. You may return the answer in any order.

The test cases are generated such that the output values fit in a 32-bit integer
and the number of different results does not exceed 104.*/

#include <cstddef>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<int> DiffWaysToCompute(string str) {
        vector<int> ans;
        for (int i = 0; i < (int)str.size(); i++) {
            if (str[i] == '+' || str[i] == '-' || str[i] == '*') {
                vector<int> const left = DiffWaysToCompute(str.substr(0, i));
                vector<int> const right = DiffWaysToCompute(str.substr(i + 1));
                for (auto x : left) {
                    for (auto y : right) {
                        if (str[i] == '+') {
                            ans.push_back(x + y);
                        }
                        if (str[i] == '-') {
                            ans.push_back(x - y);
                        }
                        if (str[i] == '*') {
                            ans.push_back(x * y);
                        }
                    }
                }
            }
        }
        if (ans.size() == 0) {
            ans.push_back(stoll(str));
        }
        return ans;
    }
};

class SolutionV2 {
   public:
    vector<int> DiffWaysToCompute(string expression) {
        int const n = expression.size();
        if (n <= 2) {
            return {stoi(expression)};
        }
        if (m_memo.count(expression)) {
            return m_memo[expression];
        }
        vector<int> result;
        string const operators = "+-*";
        size_t divider = expression.find_first_of(operators);
        while (divider != string::npos) {
            string const sub1 = expression.substr(0, divider);
            string const sub2 = expression.substr(divider + 1, n - divider - 1);
            char const op = expression[divider];
            vector<int> const nums1 = DiffWaysToCompute(sub1);
            vector<int> const nums2 = DiffWaysToCompute(sub2);
            for (int const num1 : nums1) {
                for (int const num2 : nums2) {
                    result.push_back(Calculate(num1, num2, op));
                }
            }
            divider = expression.find_first_of(operators, divider + 1);
        }
        m_memo[expression] = result;
        return result;
    }

   private:
    int Calculate(int num1, int num2, char op) {
        switch (op) {
            case '+':
                return num1 + num2;
            case '-':
                return num1 - num2;
            case '*':
                return num1 * num2;
        }
        return 0;
    }

   private:
    unordered_map<string, vector<int>> m_memo;
    /* data */
};

TEST(different_ways_to_add_parentheses, t1) {
    string const expression = "2-1-1";
    vector<int> output = {0, 2};
    Solution sl;
    vector<int> ret = sl.DiffWaysToCompute(expression);

    set<int> const ret_set(ret.begin(), ret.end());
    set<int> const out_set(output.begin(), output.end());
    /*
       ((2-1)-1) = 0
       (2-(1-1)) = 2
    */
    EXPECT_EQ(ret_set, out_set);
}

TEST(different_ways_to_add_parentheses, t2) {
    string const expression = "2*3-4*5";
    vector<int> output = {-34, -14, -10, -10, 10};
    Solution sl;
    vector<int> ret = sl.DiffWaysToCompute(expression);

    /*
       (2*(3-(4*5))) = -34
       ((2*3)-(4*5)) = -14
       ((2*(3-4))*5) = -10
       (2*((3-4)*5)) = -10
       (((2*3)-4)*5) = 10
    */
    set<int> const ret_set(ret.begin(), ret.end());
    set<int> const out_set(output.begin(), output.end());
    EXPECT_EQ(ret_set, out_set);
}

TEST(different_ways_to_add_parentheses_v2, t1) {
    string const expression = "2-1-1";
    vector<int> output = {0, 2};
    SolutionV2 sl;
    vector<int> ret = sl.DiffWaysToCompute(expression);

    set<int> const ret_set(ret.begin(), ret.end());
    set<int> const out_set(output.begin(), output.end());
    /*
       ((2-1)-1) = 0
       (2-(1-1)) = 2
    */
    EXPECT_EQ(ret_set, out_set);
}

TEST(different_ways_to_add_parentheses_v2, t2) {
    string const expression = "2*3-4*5";
    vector<int> output = {-34, -14, -10, -10, 10};
    SolutionV2 sl;
    vector<int> ret = sl.DiffWaysToCompute(expression);

    /*
       (2*(3-(4*5))) = -34
       ((2*3)-(4*5)) = -14
       ((2*(3-4))*5) = -10
       (2*((3-4)*5)) = -10
       (((2*3)-4)*5) = 10
    */
    set<int> const ret_set(ret.begin(), ret.end());
    set<int> const out_set(output.begin(), output.end());
    EXPECT_EQ(ret_set, out_set);
}

}  // namespace
