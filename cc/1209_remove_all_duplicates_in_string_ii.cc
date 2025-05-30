// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given a string s and an integer k, a k duplicate removal consists of
choosing k adjacent and equal letters from s and removing them, causing the left
and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made. It is
guaranteed that the answer is unique.
*/

#include <algorithm>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    string RemoveDuplicates(const string& s, int k) {
        /*
            1 <= s.length <= 105
            2 <= k <= 104
        */
        std::stack<char> stack;

        vector<char> v;
        for (auto& ptr : s) {
            stack.push(ptr);

            if ((int)stack.size() >= k) {
                for (int i = 0; i < k; i++) {
                    v.push_back(stack.top());
                    stack.pop();
                }

                // if all Elements in v is equal
                // then continue;
                // else
                // pop these pack
                if (!AllEuqual(v)) {
                    for (auto it = v.rbegin(); it != v.rend(); ++it) {
                        stack.push(*it);
                    }
                }
                v.clear();
            }
        }

        std::string ret;
        while (stack.size()) {
            ret += stack.top();
            stack.pop();
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    template <typename T>
    bool AllEuqual(const std::vector<T>& vec) {
        if (vec.size() == 0) {
            return true;
        }
        const T& first = vec[0];

        for (int i = 1; i < (int)vec.size(); i++) {
            if (vec[i] != first) {
                return false;
            }
        }
        return true;
    }
};

class SolutionV2 {
   public:
    struct Node {
        char m_c;   // char
        int m_cnt;  // count
    };

    string RemoveDuplicatesV2(const string& s, int k) {
        stack<Node> st;  // stack to save character and count
        for (int i = 0; i < (int)s.length(); i++) {
            if (st.empty())
                st.push({s[i], 1});
            else {
                if (st.top().m_c == s[i])
                    st.top().m_cnt++;
                else
                    st.push({s[i], 1});
            }

            if (st.top().m_cnt == k) st.pop();  // if make k len characters
        }

        // make a sentence from stack
        string ans = "";
        while (!st.empty()) {
            for (int i = 0; i < st.top().m_cnt; i++) {
                ans += st.top().m_c;
            }
            st.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    string RemoveDuplicates(const string& s, int k) {
        int const n = s.size();
        if (n < k) return s;

        stack<pair<char, int>> stk;
        for (int i = 0; i < n; ++i) {
            if (stk.empty() || stk.top().first != s[i])
                stk.emplace(s[i], 1);
            else {
                auto prev = stk.top();
                stk.pop();
                stk.emplace(s[i], prev.second + 1);
            }
            if (stk.top().second == k) stk.pop();
        }

        string ans = "";
        while (!stk.empty()) {
            auto cur = stk.top();
            stk.pop();
            while (cur.second--) {
                ans.push_back(cur.first);
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

TEST(remove_all_duplicates_in_string_ii, t1) {
    string const s = "abcd";
    int const k = 2;
    Solution sl;
    string const ret = sl.RemoveDuplicates(s, k);
    EXPECT_EQ(ret, "abcd");
}

TEST(remove_all_duplicates_in_string_ii, t2) {
    string const s = "deeedbbcccbdaa";
    int const k = 3;
    Solution sl;
    string const ret = sl.RemoveDuplicates(s, k);
    EXPECT_EQ(ret, "aa");
}

TEST(remove_all_duplicates_in_string_ii, t3) {
    string const s = "pbbcggttciiippooaais";
    int const k = 2;
    Solution sl;
    string const ret = sl.RemoveDuplicates(s, k);
    EXPECT_EQ(ret, "ps");
}

}  // namespace
