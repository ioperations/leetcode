
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
    [[nodiscard]] string RemoveOccurrences(string s, string part) const {
        int const size = static_cast<int>(s.size());
        vector<bool> exists(size, true);

        int const len = static_cast<int>(part.size());
        for (int i = 0; i < size; i++) {
            int n = 0;
            for (int j = 0; j < len; j++) {
                for (; (i + j + n) < size && !exists.at(i + j + n);) {
                    n++;
                }
                if ((i + j + n) >= size || s.at(i + j + n) != part.at(j)) {
                    break;
                }

                if (j == (len - 1)) {
                    Remove(exists, i, len);
                    i = -1;
                    break;
                }
            }
        }

        std::string ret;
        for (int i = 0; i < size; i++) {
            if (exists.at(i)) {
                ret += s.at(i);
            }
        }

        return ret;
    }

    void Remove(vector<bool>& exists, int index, int len) const {
        int const size = static_cast<int>(exists.size());
        int count = 0;
        for (int i = index; i < size; i++) {
            if (!exists.at(i)) {
                continue;
            }
            exists.at(i) = false;
            count++;
            if (count == len) {
                break;
            }
        }
    }
};

#include <gtest/gtest.h>

TEST(T0, t1) {
    string const s = "daabcbaabcbc", part = "abc";
    string const output = "dab";
    Solution const sl;
    auto ret = sl.RemoveOccurrences(s, part);
    EXPECT_EQ(ret, output);
    // Explanation: The following operations are done:
    // - s = "daabcbaabcbc", remove "abc" starting at index 2, so s =
    // "dabaabcbc".
    // - s = "dabaabcbc", remove "abc" starting at index 4, so s = "dababc".
    // - s = "dababc", remove "abc" starting at index
    //
}

TEST(T0, t2) {
    string const s = "axxxxyyyyb", part = "xy";
    string const output = "ab";
    Solution const sl;
    auto ret = sl.RemoveOccurrences(s, part);
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
