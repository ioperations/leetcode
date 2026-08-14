/*
 * Given a string s, return the maximum length of a substring such that it
 * contains at most two occurrences of each character.
 *
 * */

#include <string>
#include <unordered_map>

using namespace std;

namespace {

class Solution {
   public:
    int MaximumLengthSubstring(const string& s) {
        unordered_map<char, int> feq;

        int start = 0;
        int end = 0;
        int cnt = 0;
        int size = static_cast<int>(s.size());

        while (end < size) {
            const char& x = s[end];
            feq[x]++;

            auto it = feq.find(x);
            if (it != feq.end()) {
                while (it->second == 3) {
                    feq[s[start]]--;
                    start++;
                }
            }
            cnt = std::max(cnt, end - start + 1);

            end++;
        }

        return cnt;
    }
};

}  // namespace
   //

#include <gtest/gtest.h>

TEST(maximumLengthSubstring, t0) {
    string s = "bcbbbcba";
    int output = 4;
    Solution sl;
    int ret = sl.MaximumLengthSubstring(s);
    EXPECT_EQ(output, ret);
    // The following substring has a length of 4 and contains at most two
    // occurrences of each character: "bcba".
}

TEST(maximumLengthSubstring, t1) {
    string s = "aaaa";
    int output = 2;
    Solution sl;
    int ret = sl.MaximumLengthSubstring(s);
    EXPECT_EQ(output, ret);
    // The following substring has a length of 2 and contains at most two
    // occurrences of each character: "aa".
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
