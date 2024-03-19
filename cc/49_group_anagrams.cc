// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an array of strings strs, group the anagrams together. You can return
the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different
word or phrase, typically using all the original letters exactly once.

*/
#include <set>
#include <vector>

using namespace std;
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_map>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
class Solution {
   public:
    vector<vector<string>> GroupAnagrams(vector<string> &strs) {
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

TEST(group_anagrams, t1) {
    vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    std::vector<vector<string>> output{
        {"bat"}, {"tan", "nat"}, {"eat", "tea", "ate"}};

    std::set<vector<string>> out_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.GroupAnagrams(strs);
    EXPECT_EQ(output, ret);
}

TEST(group_anagrams, t2) {
    vector<string> strs{""};
    std::vector<vector<string>> output{{""}};

    std::set<vector<string>> out_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.GroupAnagrams(strs);
    set<vector<string>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, out_set);
}

TEST(group_anagrams, t3) {
    vector<string> strs{"a"};
    std::vector<vector<string>> output{{"a"}};

    std::set<vector<string>> out_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.GroupAnagrams(strs);
    set<vector<string>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, out_set);
}

}  // namespace
