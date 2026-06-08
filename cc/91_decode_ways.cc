/*You have intercepted a secret message encoded as a string of numbers. The
 * message is decoded via the following mapping:
 *
 * "1" -> 'A'
 *
 * "2" -> 'B'
 *
 * ...
 *
 * "25" -> 'Y'
 *
 * "26" -> 'Z'
 *
 * However, while decoding the message, you realize that there are many
different
 * ways you can decode the message because some codes are contained in other
codes
 * ("2" and "5" vs "25").
 *
 * For example, "11106" can be decoded into:
 *
 * "AAJF" with the grouping (1, 1, 10, 6)
 * "KJF" with the grouping (11, 10, 6)
 * The grouping (1, 11, 06) is invalid because "06" is not a valid code (only
"6"
 * is valid). Note: there may be strings that are impossible to decode.
 *
 * Given a string s containing only digits, return the number of ways to decode
it.
 * If the entire string cannot be decoded in any valid way, return 0.
 *
 * The test cases are generated so that the answer fits in a 32-bit integer.
 *
 * 1 <= s.length <= 100
 * s contains only digits and may contain leading zero(s).
 */
#include <array>
#include <string>
using namespace std;

namespace {

class Solution {
   public:
    int NumDecodings(const string& s) {
        for (int i = 0; i < 100; i++) {
            m_cache[i] = -1;
        }
        return s.empty() ? 0 : NumDecodings(0, s);
    }
    int NumDecodings(int p, const string& s) {
        int n = s.size();
        if (p == n) return 1;
        if (s[p] == '0')
            return 0;  // sub string starting with 0 is not a valid encoding
        if (m_cache[p] != -1) {
            return m_cache[p];
        }
        int res = NumDecodings(p + 1, s);
        if (p < n - 1 && (s[p] == '1' || (s[p] == '2' && s[p + 1] < '7')))
            res += NumDecodings(p + 2, s);
        m_cache[p] = res;
        return res;
    }

   private:
    std::array<int, 100> m_cache;
};

}  // namespace
#include <gtest/gtest.h>

TEST(numDecodings, t1) {
    std::string s = "12";

    int output = 2;
    Solution sl;
    auto ret = sl.NumDecodings(s);
    EXPECT_EQ(output, ret);

    // "12" could be decoded as "AB" (1 2) or "L" (12).
}

TEST(numDecodings, t2) {
    std::string s = "226";

    int output = 3;
    Solution sl;
    auto ret = sl.NumDecodings(s);
    EXPECT_EQ(output, ret);

    // "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
}

TEST(numDecodings, t3) {
    std::string s = "06";

    int output = 0;
    Solution sl;
    auto ret = sl.NumDecodings(s);
    EXPECT_EQ(output, ret);

    // "06" cannot be mapped to "F" because of the leading zero ("6" is
    // different from "06"). In this case, the string is not a valid encoding,
    // so return 0.
}
TEST(numDecodings, t4) {
    std::string s = "1";

    int output = 1;
    Solution sl;
    auto ret = sl.NumDecodings(s);
    EXPECT_EQ(output, ret);

    // "06" cannot be mapped to "F" because of the leading zero ("6" is
    // different from "06"). In this case, the string is not a valid encoding,
    // so return 0.
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
