/*
 * Given a positive integer n, return the punishment number of n.
 * The punishment number of n is defined as the sum of the squares of all
 * integers
 * i such that:
 *
 * 1 <= i <= n
 * The decimal representation of i * i can be partitioned into contiguous
 * substrings such that the sum of the integer values of these substrings
 * equals i.
 */

#include <set>
#include <unordered_map>

class Solution {
   public:
    int punishmentNumber(int n) {
        // 1 <= n <= 1000
        int ret = 0;
        int i = 1;
        for (; i <= n; i++) {
            int doubleValue = i * i;
            auto q = gen(doubleValue);
            if (q.count(i) > 0) {
                ret += doubleValue;
            }
        }
        return ret;
    }

    std::set<int> gen(int n) {
        std::set<int> ret;
        ret.emplace(n);
        if (n < 10) {
            return ret;
        }

        if (cache.count(n)) {
            return cache[n];
        }
        int i = 1;
        int len = getlen(n);
        while (i < len) {
            int q = getDouble(i);
            int m = n % q;
            int t = n / q;

            const auto &mRet = gen(m);
            const auto &nRet = gen(t);

            for (auto mptr : mRet) {
                for (auto nptr : nRet) {
                    ret.emplace(mptr + nptr);
                }
            }
            i++;
        }

        cache[n] = ret;

        return ret;
    }

    int getDouble(int i) {
        int ret = 1;
        for (int j = 0; j < i; j++) {
            ret = ret * 10;
        }

        return ret;
    }

    int getlen(int n) {
        int i = 0;
        for (; n > 0;) {
            i++;
            n = n / 10;
        }
        return i;
    }
    std::unordered_map<int, std::set<int>> cache;
};

#include <gtest/gtest.h>
TEST(t0, t0) {
    int n = 1296;

    Solution sl;
    std::set<int> ret = sl.gen(n);
    std::set<int> expect{18, 27, 36, 99, 108, 135, 297, 1296};

    EXPECT_EQ(ret, expect);
}

TEST(t0, t1) {
    int n = 10;
    int Output = 182;

    Solution sl;
    int ret = sl.punishmentNumber(n);
    EXPECT_EQ(ret, Output);
    // Explanation: There are exactly 3 integers i in the range [1, 10] that
    // satisfy the conditions in the statement:
    // - 1 since 1 * 1 = 1
    // - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 and 1 with a sum
    // equal to 8 + 1 == 9.
    // - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 and 0 with a
    // sum equal to 10 + 0 == 10. Hence, the punishment number of 10 is 1 + 81 +
    // 100 = 182
}

TEST(t0, t2) {
    int n = 37;
    int Output = 1478;

    Solution sl;
    int ret = sl.punishmentNumber(n);
    EXPECT_EQ(ret, Output);
    //  There are exactly 4 integers i in the range [1, 37] that satisfy the
    //  conditions in the statement:
    // - 1 since 1 * 1 = 1.
    // - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 + 1.
    // - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 + 0.
    // - 36 since 36 * 36 = 1296 and 1296 can be partitioned into 1 + 29 + 6.
    // Hence, the punishment number of 37 is 1 + 81 + 100 + 1296 = 1478
}

TEST(t0, t3) {
    // FIXME: timeout
    int n = 1000;
    int Output = 10804657;

    Solution sl;
    int ret = sl.punishmentNumber(n);
    EXPECT_EQ(ret, Output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
