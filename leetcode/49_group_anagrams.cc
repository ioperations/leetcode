/*Given an array of strings strs, group the anagrams together. You can return
the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different
word or phrase, typically using all the original letters exactly once.

*/
#include <vector>
using namespace std;
#include <algorithm>
#include <string>
#include <unordered_map>

class Solution {
   public:
    vector<vector<string>> GroupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mapp;
        for (auto str : strs) {
            string st = str;
            sort(st.begin(), st.end());
            mapp[st].push_back(str);
        }
        vector<vector<string>> ans;
        for (auto x : mapp) {
            ans.push_back(x.second);
        }
        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <set>

TEST(t0, t1) {
    vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    std::vector<vector<string>> output{
        {"bat"}, {"tan", "nat"}, {"eat", "tea", "ate"}};

    std::set<vector<string>> out_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.GroupAnagrams(strs);
    EXPECT_EQ(output, ret);
}

TEST(t0, t2) {
    vector<string> strs{""};
    std::vector<vector<string>> output{{""}};

    std::set<vector<string>> out_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.GroupAnagrams(strs);
    set<vector<string>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, out_set);
}

TEST(t0, t3) {
    vector<string> strs{"a"};
    std::vector<vector<string>> output{{"a"}};

    std::set<vector<string>> out_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.GroupAnagrams(strs);
    set<vector<string>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, out_set);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
