/*
    Given a string s that contains parentheses and letters, remove the minimum
    number of invalid parentheses to make the input string valid.
    Return all the possible results. You may return the answer in any order.
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   public:
    unordered_map<string, int> mp;

    void Helper(string s, int minrem, vector<string> &st) {
        if (mp[s] != 0) return;
        mp[s]++;
        if (minrem < 0) return;
        if (minrem == 0) {
            int x = RemovalsV2(s);
            if (x == 0) st.push_back(s);
            return;
        }
        for (int i = 0; i < (int)s.length(); i++) {
            string left = s.substr(0, i);
            string right = s.substr(i + 1);
            Helper(left + right, minrem - 1, st);
        }
    }

    int Removals(string s) {
        stack<char> st;
        for (int i = 0; i < (int)s.length(); i++) {
            if (s[i] == '(') {
                st.push(s[i]);
            } else if (s[i] == ')') {
                if (st.size() == 0 || st.top() == ')')
                    st.push(s[i]);
                else
                    st.pop();
            }
        }
        return st.size();
    }

    int RemovalsV2(string s) {
        stack<char> stack;

        for (auto &ptr : s) {
            if (ptr == '(') {
                stack.push(ptr);
            } else if (ptr == ')') {
                if (stack.size() && stack.top() != ')')
                    stack.pop();
                else
                    stack.push(ptr);
            }
        }
        return stack.size();
    }

    vector<string> RemoveInvalidParentheses(string s) {
        int minrems = RemovalsV2(s);
        vector<string> ans;
        Helper(s, minrems, ans);
        return ans;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    string s = "()())()";
    vector<string> output = {"(())()", "()()()"};

    Solution sl;
    auto ret = sl.RemoveInvalidParentheses(s);
    set<string> ret_set(ret.begin(), ret.end());
    set<string> output_set(output.begin(), output.end());
    EXPECT_EQ(ret_set, output_set);
}

TEST(t0, t2) {
    string s = "(a)())()";
    vector<string> output = {"(a())()", "(a)()()"};

    Solution sl;
    auto ret = sl.RemoveInvalidParentheses(s);
    set<string> ret_set(ret.begin(), ret.end());
    set<string> output_set(output.begin(), output.end());
    EXPECT_EQ(ret_set, output_set);
}

TEST(t0, t3) {
    string s = ")(";
    vector<string> output = {""};

    Solution sl;
    auto ret = sl.RemoveInvalidParentheses(s);
    set<string> ret_set(ret.begin(), ret.end());
    set<string> output_set(output.begin(), output.end());
    EXPECT_EQ(ret_set, output_set);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
