/*
 *
 *   You are given a 0-indexed string pattern of length n consisting of the
 * characters 'I' meaning increasing and 'D' meaning decreasing.
 *
 * A 0-indexed string num of length n + 1 is created using the following
 * conditions:
 *
 * num consists of the digits '1' to '9', where each digit is used at most once.
 * If pattern[i] == 'I', then num[i] < num[i + 1].
 * If pattern[i] == 'D', then num[i] > num[i + 1].
 * Return the lexicographically smallest possible string num that meets the
 * conditions.
 */
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    string smallestNumber(string pattern) {
        // 1 <= pattern.length <= 8
        // pattern consists of only the letters 'I' and 'D'.
        string ret;

        this->pattern = pattern;
        auto size = pattern.size();

        ret.resize(size + 1);

        vector<bool> visiable(9, true);
        Gen(ret, 0, size + 1, visiable);
        return ret;
    }

    bool Gen(string &ret, int index, int size, vector<bool> &visiable) {
        if (index == size) {
            if (checkFunc(ret)) {
                return true;
            }
            return false;
        }

        for (int i = 1; i < 10; i++) {
            if (visiable[i - 1]) {
                ret[index] = '0' + i;
                visiable[i - 1] = false;
                if (Gen(ret, index + 1, size, visiable)) {
                    return true;
                }
                visiable[i - 1] = true;
            }
        }
        return false;
    }

    bool checkFunc(const string &str) {
        for (int i = 0; i < pattern.size(); i++) {
            if (pattern[i] == 'I') {
                if (str[i] >= str[i + 1]) {
                    return false;
                }
            } else {
                if (str[i] <= str[i + 1]) {
                    return false;
                }
            }
        }

        return true;
    }

    string pattern;
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    string pattern = "IIIDIDDD";

    string output = "123549876";
    Solution sl;
    auto ret = sl.smallestNumber(pattern);
    EXPECT_EQ(output, ret);
    // Explanation:
    // At indices 0, 1, 2, and 4 we must have that num[i] < num[i+1].
    // At indices 3, 5, 6, and 7 we must have that num[i] > num[i+1].
    // Some possible values of num are "245639871", "135749862", and
    // "123849765". It can be proven that "123549876" is the smallest possible
    // num that meets the conditions. Note that "123414321" is not possible
    // because the digit '1' is used more than once.
}

TEST(t0, t2) {
    string pattern = "DDD";

    string output = "4321";
    Solution sl;
    auto ret = sl.smallestNumber(pattern);
    EXPECT_EQ(output, ret);
    // Some possible values of num are "9876", "7321", and "8742".
    // It can be proven that "4321" is the smallest possible num that meets the
    // conditions.
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
