// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a string s, partition s such that every substring of the partition is a
palindrome. Return all possible palindrome partitioning of s.

A palindrome string is a string that reads the same backward as forward.*/

#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace { 
class Solution {
   public:
    vector<vector<string>> Partition(string s) {
        return Partition(s, 0, s.size() - 1);
    }
    vector<vector<string>> Partition(string &s, int begin, int end) {
        vector<vector<string>> ret;

        for (int i = begin; i <= end; i++) {
            if (IsPalindrom(s, begin, i)) {
                auto ret1 = Partition(s, i + 1, end);

                if (ret1.size()) {
                    for (auto &ptr : ret1) {
                        ptr.insert(ptr.begin(), s.substr(begin, i - begin + 1));
                    }
                    for (auto &ptr : ret1) {
                        ret.push_back(ptr);
                    }
                } else {
                    ret.push_back(
                        vector<std::string>{s.substr(begin, i - begin + 1)});
                }
            }
        }

        return ret;
    }

    bool IsPalindrom(std::string &s, int left, int right) {
        while (left < right) {
            if (s[left] == s[right]) {
                left++;
                right--;
            } else {
                return false;
            }
        }
        return true;
    }
};


TEST(t0, t1) {
    string s = "aab";
    vector<vector<string>> output = {{"a", "a", "b"}, {"aa", "b"}};

    Solution sl;
    auto ret = sl.Partition(s);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string s = "a";
    vector<vector<string>> output = {{"a"}};

    Solution sl;
    auto ret = sl.Partition(s);
    EXPECT_EQ(ret, output);
}

}
