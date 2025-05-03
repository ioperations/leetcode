
/*
 * Given two strings s and part, perform the following operation on s until all
 * occurrences of the substring part are removed:
 *
 * Find the leftmost occurrence of the substring part and remove it from s.
 * Return s after removing all occurrences of part.
 *
 * A substring is a contiguous sequence of characters in a string.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    string removeOccurrences(string s, string part) {
        // FIXME: not effciency
        /**
         * 1 <= s.length <= 1000
         * 1 <= part.length <= 1000
         * s and part consists of lowercase English letters.
         */
        size_t size = s.size();
        vector<bool> exists(size, true);

        size_t len = part.size();
        for (int i = 0; i < size; i++) {
            int n = 0;
            for (int j = 0; j < len; j++) {
                for (; (i + j + n) < size && !exists[i + j + n];) {
                    n++;
                }
                if (s[i + j + n] != part[j]) {
                    break;
                }

                if (j == (len - 1)) {
                    remove(exists, i, len);
                    i = -1;
                    break;
                }
            }
        }

        std::string ret;
        for (int i = 0; i < size; i++) {
            if (exists[i]) {
                ret += s[i];
            }
        }

        return ret;
    }

    void remove(vector<bool>& exists, int index, int len) {
        auto size = exists.size();
        int count = 0;
        for (int i = index; i < size; i++) {
            if (!exists[i]) {
                continue;
            }
            exists[i] = false;
            count++;
            if (count == len) {
                break;
            }
        }
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    string s = "daabcbaabcbc", part = "abc";
    string output = "dab";
    Solution sl;
    auto ret = sl.removeOccurrences(s, part);
    EXPECT_EQ(ret, output);
    // Explanation: The following operations are done:
    // - s = "daabcbaabcbc", remove "abc" starting at index 2, so s =
    // "dabaabcbc".
    // - s = "dabaabcbc", remove "abc" starting at index 4, so s = "dababc".
    // - s = "dababc", remove "abc" starting at index
    //
}

TEST(t0, t2) {
    string s = "axxxxyyyyb", part = "xy";
    string output = "ab";
    Solution sl;
    auto ret = sl.removeOccurrences(s, part);
    EXPECT_EQ(ret, output);
    // Explanation:
    //     The following operations are done:
    // - s = "axxxxyyyyb", remove "xy" starting at index 4 so s = "axxxyyyb".
    // - s = "axxxyyyb", remove "xy" starting at index 3 so s = "axxyyb".
    // - s = "axxyyb", remove "xy" starting at index 2 so s = "axyb".
    // - s = "axyb", remove "xy" starting at index 1 so s = "ab".
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
