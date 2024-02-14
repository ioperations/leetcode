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
#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    std::string ReverseVowels(std::string s) {
        // pass
        std::stack<int> z;
        std::queue<char> num;

        std::set<char> vowels{'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

        for (int i = 0; i < (int)s.size(); i++) {
            if (vowels.count(s[i])) {
                z.push(i);
                num.push(s[i]);
            }
        }
        while (z.size()) {
            int d = z.top();

            s[d] = num.front();
            num.pop();
            z.pop();
        }
        return s;
    }
};



TEST(t0, t1) {
    std::string s = "hello";
    std::string output = "holle";
    Solution sl;
    auto ret = sl.ReverseVowels(s);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    std::string s = "leetcode";
    std::string output = "leotcede";
    Solution sl;
    auto ret = sl.ReverseVowels(s);
    EXPECT_EQ(ret, output);
}

}
