// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a string s, reverse only all the vowels in the string and return it.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both cases.
*/

#include <queue>
#include <set>
#include <stack>
#include <string>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    std::string ReverseVowels(std::string s) {
        // pass
        std::stack<int> z;
        std::queue<char> num;

        std::set<char> const vowels{'a', 'e', 'i', 'o', 'u',
                                    'A', 'E', 'I', 'O', 'U'};

        for (int i = 0; i < (int)s.size(); i++) {
            if (vowels.count(s[i])) {
                z.push(i);
                num.push(s[i]);
            }
        }
        while (z.size()) {
            int const d = z.top();

            s[d] = num.front();
            num.pop();
            z.pop();
        }
        return s;
    }
};

TEST(reverse_vowels_of_a_string, t1) {
    std::string const s = "hello";
    std::string const output = "holle";
    Solution sl;
    auto ret = sl.ReverseVowels(s);
    EXPECT_EQ(ret, output);
}

TEST(reverse_vowels_of_a_string, t2) {
    std::string const s = "leetcode";
    std::string const output = "leotcede";
    Solution sl;
    auto ret = sl.ReverseVowels(s);
    EXPECT_EQ(ret, output);
}

}  // namespace
