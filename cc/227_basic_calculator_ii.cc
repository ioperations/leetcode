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

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

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
            char ch = s[j];
            if (ch == '+' or ch == '-') {
                op.push(ch);
            } else if (ch == '/' or ch == '*') {
                int lastval = values.top();
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
            int b = values.top();
            values.pop();
            char ch = op.top();
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
    string s = "3+2*2";
    int output = 7;
    Solution sl;
    int ret = sl.Calculate(s);
    EXPECT_EQ(ret, output);
}

TEST(basic_calculator_ii, t2) {
    string s = " 3/2 ";
    int output = 1;
    Solution sl;
    int ret = sl.Calculate(s);
    EXPECT_EQ(ret, output);
}

TEST(basic_calculator_ii, t3) {
    string s = " 3+5 / 2 ";
    int output = 5;
    Solution sl;
    int ret = sl.Calculate(s);
    EXPECT_EQ(ret, output);
}

} // namespace
