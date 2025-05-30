// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the
square brackets is being repeated exactly k times. Note that k is guaranteed to
be a positive integer.

You may assume that the input string is always valid; there are no extra white
spaces, square brackets are well-formed, etc. Furthermore, you may assume that
the original data does not contain any digits and that digits are only for those
repeat numbers, k. For example, there will not be input like 3a or 2[4].

The test cases are generated so that the length of the output will never exceed
105.*/

#include <cctype>
#include <stack>
#include <string>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;
using namespace std;

#include <gtest/gtest.h>
namespace {
class Solution {
   public:
    string DecodeString(string encoded_string) {
        stack<string> st;
        string curr = "";
        string num = "";
        for (char const i : encoded_string) {
            if (isalpha(i)) curr += i;
            if (isdigit(i)) num += i;
            if (i == '[') {
                st.push(curr);
                st.push(num);
                num = "";
                curr = "";
            }
            if (i == ']') {
                int const to_repeat = stoi(st.top());
                st.pop();
                string left_part_plus_repeat = st.top();
                st.pop();
                for (int i = 0; i < to_repeat; i++)
                    left_part_plus_repeat += curr;
                curr = left_part_plus_repeat;
            }
        }
        return curr;
    }
};

TEST(decode_string, t1) {
    string const s = "3[a]2[bc]";
    string const out = "aaabcbc";
    Solution sl;
    auto ret = sl.DecodeString(s);
    EXPECT_EQ(ret, out);
}

TEST(decode_string, t2) {
    string const s = "3[a2[c]]";
    string const out = "accaccacc";
    Solution sl;
    auto ret = sl.DecodeString(s);
    EXPECT_EQ(ret, out);
}

TEST(decode_string, t3) {
    string const s = "2[abc]3[cd]ef";
    string const out = "abcabccdcdcdef";
    Solution sl;
    auto ret = sl.DecodeString(s);
    EXPECT_EQ(ret, out);
}

using namespace Tree;
#include <vector>

TEST(decode_string, t4) {
#define null std::optional<int>()
    std::vector<int> const values{1, 2, 3, 4, 5, 6, 7};
    TreeNode<int>* n = ConstructTree<int>(values);
    FreeTreeNode<int>(n);
}

}  // namespace
