// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a string s which represents an expression, evaluate this expression and
return its value.

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate
results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings
as mathematical expressions, such as eval().*/
#include <string>

using namespace std;
#include <stack>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    int Calculate(string s) {
        int i = 0;
        for (int j = 0; j < (int)s.size(); j++) {
            if (s[j] != ' ') {
                s[i++] = s[j];
            }
        }
        s = s.substr(0, i);
        // I have removed all spaces
        stack<int> values;
        stack<char> op;
        for (int j = 0; j < i; j++) {
            char const ch = s[j];
            if (ch == '+' or ch == '-') {
                op.push(ch);
            } else if (ch == '/' or ch == '*') {
                int const lastval = values.top();
                values.pop();
                int nextval = 0;
                j++;
                while (s[j] <= '9' and s[j] >= '0') {
                    nextval *= 10;
                    nextval += (int)(s[j] - '0');
                    j++;
                }
                j--;
                if (ch == '/') {
                    values.push(lastval / nextval);
                } else {
                    values.push(lastval * nextval);
                }

            } else {
                int val = 0;
                while (s[j] <= '9' and s[j] >= '0') {
                    val *= 10;
                    val += (int)(s[j] - '0');
                    j++;
                }
                j--;
                values.push(val);
            }
        }
        int ans = 0;
        while (!op.empty()) {
            int const b = values.top();
            values.pop();
            char const ch = op.top();
            op.pop();
            // cout<<a<<" "<<ch<<" "<<b<<endl;
            if (ch == '+') {
                ans += b;
            } else {
                ans -= b;
            }
        }
        ans += values.top();
        return ans;
    }
};

TEST(basic_calculator_ii, t1) {
    string const s = "3+2*2";
    int const output = 7;
    Solution sl;
    int const ret = sl.Calculate(s);
    EXPECT_EQ(ret, output);
}

TEST(basic_calculator_ii, t2) {
    string const s = " 3/2 ";
    int const output = 1;
    Solution sl;
    int const ret = sl.Calculate(s);
    EXPECT_EQ(ret, output);
}

TEST(basic_calculator_ii, t3) {
    string const s = " 3+5 / 2 ";
    int const output = 5;
    Solution sl;
    int const ret = sl.Calculate(s);
    EXPECT_EQ(ret, output);
}

}  // namespace
