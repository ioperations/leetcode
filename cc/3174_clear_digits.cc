/*
 * You are given a string s.
 * Your task is to remove all digits by doing this operation repeatedly:
 *
 * Delete the first digit and the closest non-digit character to its left.
 * Return the resulting string after removing all digits.
 *
 */

#include <cstddef>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    string ClearDigits(string s) {
        // 1 <= s.length <= 100
        // s consists only of lowercase English letters and digits.
        // The input is generated such that it is possible to delete all digits.
        auto size = s.size();
        vector<bool> exists(size, true);
        for (size_t i = 0; i < size; i++) {
            if ('0' <= s[i] && s[i] <= '9') {
                exists[i] = false;
                for (int j = i - 1; j >= 0; j--) {
                    if (exists[j]) {
                        exists[j] = false;
                        break;
                    }
                }
            }
        }
        string ret;
        for (size_t i = 0; i < size; i++) {
            if (exists[i]) {
                ret += s[i];
            }
        }
        return ret;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    std::string const s = "abc";

    std::string const output = "abc";
    Solution sl;
    auto ret = sl.ClearDigits(s);
    EXPECT_EQ(ret, output);

    // Explanation:
    // There is no digit in the string.
}

TEST(t0, t2) {
    std::string const s = "cb34";

    std::string const output = "";
    Solution sl;
    auto ret = sl.ClearDigits(s);
    EXPECT_EQ(ret, output);
    /*
     * First, we apply the operation on s[2], and s becomes "c4".
     * Then we apply the operation on s[1], and s becomes "".
     */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
