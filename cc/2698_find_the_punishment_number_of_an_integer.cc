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
    int PunishmentNumber(int n) {
        // 1 <= n <= 1000
        int ret = 0;
        int i = 1;
        for (; i <= n; i++) {
            int const double_value = i * i;
            auto q = Gen(double_value);
            if (q.count(i) > 0) {
                ret += double_value;
            }
        }
        return ret;
    }

    std::set<int> Gen(int n) {
        std::set<int> ret;
        ret.emplace(n);
        if (n < 10) {
            return ret;
        }

        if (m_cache.count(n)) {
            return m_cache[n];
        }
        int i = 1;
        int const len = Getlen(n);
        while (i < len) {
            int const q = GetDouble(i);
            int const m = n % q;
            int const t = n / q;

            const auto& m_ret = Gen(m);
            const auto& n_ret = Gen(t);

            for (auto mptr : m_ret) {
                for (auto nptr : n_ret) {
                    ret.emplace(mptr + nptr);
                }
            }
            i++;
        }

        m_cache[n] = ret;

        return ret;
    }

    int GetDouble(int i) {
        int ret = 1;
        for (int j = 0; j < i; j++) {
            ret = ret * 10;
        }

        return ret;
    }

    int Getlen(int n) {
        int i = 0;
        for (; n > 0;) {
            i++;
            n = n / 10;
        }
        return i;
    }
    std::unordered_map<int, std::set<int>> m_cache;
};

#include <gtest/gtest.h>
TEST(t0, t0) {
    int const n = 1296;

    Solution sl;
    std::set<int> const ret = sl.Gen(n);
    std::set<int> const expect{18, 27, 36, 99, 108, 135, 297, 1296};

    EXPECT_EQ(ret, expect);
}

TEST(t0, t1) {
    int const n = 10;
    int const output = 182;

    Solution sl;
    int const ret = sl.PunishmentNumber(n);
    EXPECT_EQ(ret, output);
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
    int const n = 37;
    int const output = 1478;

    Solution sl;
    int const ret = sl.PunishmentNumber(n);
    EXPECT_EQ(ret, output);
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
    int const n = 1000;
    int const output = 10804657;

    Solution sl;
    int const ret = sl.PunishmentNumber(n);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
